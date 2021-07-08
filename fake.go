package main

import (
	"crypto/rand"
	"crypto/sha256"
	"fmt"
)

var wallet map[[32]byte][21][32]byte
var segments_stack map[[32]byte][72]byte
var segments_transaction_next map[[32]byte][2][32]byte
var purse map[[32]byte][64]byte
var contracts []contract

func stack_decode(b []byte) (changeto [32]byte, sumto [32]byte, sum uint64) {

	copy(changeto[0:], b[0:32])
	copy(sumto[0:], b[32:64])

	sum = uint64(b[64])
	sum <<= 8
	sum += uint64(b[65])
	sum <<= 8
	sum += uint64(b[66])
	sum <<= 8
	sum += uint64(b[67])
	sum <<= 8
	sum += uint64(b[68])
	sum <<= 8
	sum += uint64(b[69])
	sum <<= 8
	sum += uint64(b[70])
	sum <<= 8
	sum += uint64(b[71])

	return changeto, sumto, sum
}

func decider_key_to_short_decider(key [64]byte) (o [32]byte) {
	var buf3_a0 [96]byte
	copy(buf3_a0[32:96], key[0:])
	for i := uint32(0); i < 65535; i++ {
		o = sha256.Sum256(buf3_a0[32:64])
		copy(buf3_a0[32:64], o[0:])
		o = sha256.Sum256(buf3_a0[64:96])
		copy(buf3_a0[64:96], o[0:])
	}
	o = sha256.Sum256(buf3_a0[0:])
	return o
}

func decider_key_to_long_decider(key [64]byte, message uint16) (ret [2][32]byte) {
	var o [32]byte
	for i := uint32(0); i < uint32(message); i++ {
		o = sha256.Sum256(key[0:32])
		copy(key[0:32], o[0:])
	}
	for i := uint32(0); i < 65535-uint32(message); i++ {
		o = sha256.Sum256(key[32:])
		copy(key[32:64], o[0:])
	}
	copy(ret[0][0:], key[0:32])
	copy(ret[1][0:], key[32:64])
	return ret
}

func comb_trade_generate_branch(trade_bit uint16, branch_id uint16, forward_address, rollback_address [32]byte) [18][32]byte {
	var buf [65536][32]byte
	for i := range buf {

		if (uint16(i) & trade_bit) == trade_bit {
			buf[i] = forward_address
		} else {
			buf[i] = rollback_address
		}
	}
	return merkle_tree_generate_branch(&buf, branch_id)
}

func merkle_tree_generate_branch(tree *[65536][32]byte, branch_id uint16) (branch [18][32]byte) {
	branch[0] = (*tree)[branch_id]
	for j := 0; j < 16; j++ {

		branch[j+1] = (*tree)[branch_id^1]

		for i := 0; i < 1<<uint(15-j); i++ {
			(*tree)[i] = merkle((*tree)[2*i][0:], (*tree)[2*i+1][0:])
		}
		branch_id >>= 1
	}
	branch[17] = (*tree)[0]
	return branch
}

func merkle(a []byte, b []byte) [32]byte {
	var buf [64]byte
	var sli []byte
	sli = buf[0:0]

	sli = append(sli, a[0:]...)
	sli = append(sli, b[0:]...)

	return sha256.Sum256(sli)
}

func uint16_reverse(n uint16) uint16 {
	n = ((n >> 1) & 0x5555) | ((n << 1) & 0xaaaa)
	n = ((n >> 2) & 0x3333) | ((n << 2) & 0xcccc)
	n = ((n >> 4) & 0x0f0f) | ((n << 4) & 0xf0f0)
	n = ((n >> 8) & 0x00ff) | ((n << 8) & 0xff00)
	return n
}

func byte2hex(b []byte) string {
	return fmt.Sprintf("%X", b)
}

func randbyte32() (out [32]byte) {
	rand.Read(out[0:])
	return
}

func randhex32() (out string) {
	r := randbyte32()
	return byte2hex(r[:])
}

func random_key() [32]byte {
	var rawkey [672]byte
	var key [21][32]byte
	var buf [672]byte
	var sli []byte
	sli = buf[0:0]

	rand.Read(rawkey[0:])

	for i := 0; i < 21; i++ {
		copy(key[i][0:], rawkey[32*i:32*i+32])
		tip := key[i]
		for j := 0; j < 59213; j++ {
			tip = sha256.Sum256(tip[0:])
		}
		sli = append(sli, tip[0:]...)
	}
	pub := sha256.Sum256(sli)
	wallet[pub] = key
	return pub
}

func random_stack() [32]byte {
	var rawdata [72]byte
	rand.Read(rawdata[:])
	var hash = sha256.Sum256(rawdata[0:])
	segments_stack[hash] = rawdata
	return hash
}

func random_tx() {
	from := random_key()
	to := random_stack()
	var txidandto [2][32]byte
	var data [64]byte
	copy(data[0:32], from[:])
	copy(data[32:], to[:])
	txidandto[0] = sha256.Sum256(data[:])
	txidandto[1] = to
	segments_transaction_next[from] = txidandto
}

func random_decider() [32]byte {
	var secret [64]byte
	rand.Read(secret[:])
	short := decider_key_to_short_decider(secret)
	purse[short] = secret
	return short
}

func random_contract() {
	var c contract
	forward := random_stack()
	c.forward = byte2hex(forward[:])
	roll := random_stack()
	c.rollback = byte2hex(roll[:])
	short := random_decider()
	c.short_decider = decode_decider(short, purse[short])
	c.mask = 1

	branch := comb_trade_generate_branch(uint16_reverse(c.mask), 0, forward, roll)
	address := merkle(short[0:], branch[17][0:])
	c.address = byte2hex(address[:])

	contracts = append(contracts, c)
}

func nats_to_comb(nats uint64) string {
	s := fmt.Sprintf("%09d", nats)
	point := len(s) - 8
	end := len(s)
	for s[end-1] == '0' {
		end -= 1
	}
	s = s[0:point] + "." + s[point:end]
	return s
}

func init() {
	wallet = make(map[[32]byte][21][32]byte)
	segments_stack = make(map[[32]byte][72]byte)
	segments_transaction_next = make(map[[32]byte][2][32]byte)
	purse = make(map[[32]byte][64]byte)
	contracts = make([]contract, 0)

	random_key()
	random_key()
	random_stack()
	random_stack()
	random_tx()
	random_decider()
	random_contract()
}
