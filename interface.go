package main

import (
	"crypto/sha256"
	"fmt"
	"sort"
)

type keypair struct {
	public  string
	private [21]string
	label   string
}

type stack struct {
	address     string
	destination string
	sum         uint64
	change      string
	label       string
}

type transaction struct {
	id          string
	source      string
	destination string
}

type decider struct {
	secrets       [2]string
	short_decider string
	long_decider  string
	sign          uint16
	label         string
}

type contract struct {
	address       string
	forward       string
	rollback      string
	mask          uint16
	short_decider decider
	label         string
}

func decode_key(public [32]byte, private [21][32]byte) (key keypair) {
	key.public = byte2hex(public[:])
	var private_hex [21]string
	for i, p := range private {
		private_hex[i] = byte2hex(p[:])
	}
	key.private = private_hex
	return
}

func decode_stack(data [72]byte) (stack stack) {
	changeto, sumto, sum := stack_decode(data[:])
	address := sha256.Sum256(data[:])
	stack.address = byte2hex(address[:])
	stack.change = byte2hex(changeto[:])
	stack.destination = byte2hex(sumto[:])
	stack.sum = uint64(sum)
	return
}

func decode_transaction(source [32]byte, data [2][32]byte) (tx transaction) {
	tx.source = byte2hex(source[:])
	tx.destination = byte2hex(data[1][:])
	tx.id = byte2hex(data[0][:])
	return
}

func decode_decider(short [32]byte, secrets [64]byte) (dec decider) {
	dec.short_decider = byte2hex(short[:])
	dec.secrets[0] = byte2hex(secrets[0:32])
	dec.secrets[1] = byte2hex(secrets[32:64])
	dec.long_decider = ""
	return
}

func get_keys() []keypair {
	keys := make([]keypair, 0)
	for k, v := range wallet {
		keys = append(keys, decode_key(k, v))
	}
	sort.Slice(keys[:], func(i, j int) bool {
		return keys[i].public < keys[j].public
	})
	return keys
}

func get_stacks() []stack {
	stacks := make([]stack, 0)
	for _, v := range segments_stack {
		stacks = append(stacks, decode_stack(v))
	}
	sort.Slice(stacks[:], func(i, j int) bool {
		return stacks[i].address < stacks[j].address
	})
	return stacks
}

func get_transactions() []transaction {
	txs := make([]transaction, 0)
	for k, v := range segments_transaction_next {
		txs = append(txs, decode_transaction(k, v))
	}
	sort.Slice(txs[:], func(i, j int) bool {
		return txs[i].id < txs[j].id
	})
	return txs
}

func get_deciders() []decider {
	deciders := make([]decider, 0)
	for k, v := range purse {
		deciders = append(deciders, decode_decider(k, v))
	}
	sort.Slice(deciders, func(i, j int) bool {
		return deciders[i].short_decider < deciders[j].short_decider
	})
	return deciders
}

func get_contracts() []contract {
	return contracts
}

func create_keypair(label string) {
	fmt.Printf("create_keypair(%s)\n", label)
}

func create_stack(label, destination, change string, sum uint64) {
	fmt.Printf("create_stack(%s, %s, %s, %d)\n", label, destination, change, sum)
}

func create_contract(label, forward, rollback, short_decider string, mask uint16) {
	fmt.Printf("create_contract(%s, %s, %s, %s, %d)\n", label, forward, rollback, short_decider, mask)
}

func create_decider(label, secret_one, secret_two string) {
	fmt.Printf("create_decider(%s, %s, %s)\n", label, secret_one, secret_two)
}

func make_claim(address string, fee, amount uint16) {
	fmt.Printf("make_claim(%s, %d, %d)\n", address, fee, amount)
}

func make_transaction(from, to string) {
	fmt.Printf("make_transaction(%s, %s)\n", from, to)
}

func redeem_contract(contract, decider string) {
	fmt.Printf("redeem_contract(%s, %s)\n", contract, decider)
}

func decide_decider(decider string, sign uint16) {
	fmt.Printf("decide_decider(%s, %d)\n", decider, sign)
}
