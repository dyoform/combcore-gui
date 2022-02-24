COMBCore GUI
--------
Qt GUI for [COMBCore](https://github.com/dyoform/combcore).

Built using Qt 5.15.2. Binaries can be found in the release's of COMBCore, these are dynamially linked to Qt on linux, and statically linked on Windows.

If combcore is found in the same directory as combcore-qt then it will be started as a child process.
If started as a child process the output of combcore can be seen in the Settings tab.

A status of "Disconnected" means combcore-qt is unable to connect to the combcore daemon.

Some features of COMBCore are not yet exposed through the GUI, the "Custom Action" needs to be used in these cases, see available actions [here](https://github.com/dyoform/combcore/blob/master/control.go).


Committing
----------
Any address that needs to be committed will be shown in the pending-for-commit table in the Overview tab.
Transactions and Merkle Segments will automatically load their signatures into this table (if they are not already committed).

For security reasons COMBCore cannot currently send BTC transactions on its own, I have however made it as painless as possible to commit addresses manually.

Pressing the star button will commit all addresses in the table, encode them into a raw BTC transaction, and copy it into your clipboard.
Then you can fund, sign and send the transaction in Bitcoin Core like so:
```
fundrawtransaction 'RAW_TRANSACTION_HEX'
signrawtransactionwithwallet 'FUNDED_HEX'
sendrawtransaction 'SIGNED_HEX'
```

Claiming
--------
Heres the rundown of how to claim:
- Create a Key.
- Create a Stack with change set to the Key address, destination set to all zeros, sum set to 0.
- Save the wallet to a new file.
- Use the "Commit Address" action on the Stack address.
- There should now be an address labeled Claim in the Pending table.
- Press the star button, the raw transaction hex will be loaded into your clipboard.
- Fund, sign and send the transaction in Bitcoin Core.

A claim also needs a much higher fee rate which is set by:
```
fundrawtransaction 'RAW_TRANSACTION_HEX' '{"fee_rate":300}'
```
This sets the sats/vbyte for the whole transaction, so its recommend the claim be the only output.