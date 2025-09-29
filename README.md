# Codex-Infernum
This is a criptografy that I created for fun and I'll use it for an enigma, that some friends will solve.
## How to use?
- First: Compile;
  ```bash
  gcc readbin.c -o readbin
  gcc genbin.c -o genbin
  ```
- Second: Create your `latin.bin`, or pick the one that someone handed you;
  ```bash
  ./genbin
  ```
- Third: Use the encryptor;
  ```bash
  ./readbin -e latin.bin "your message"
  ```
- Optional: test the decryptor.
  You need to insert the `KEY` that's generated with the encrypted message.
  ```bash
  ./readbin -d "encrypted message"
  ```
### EXTRA
- test the criptography!
```bash
est stultus septimus pes sanus rivus hic postquam octo aliquis igitur aliquid ager idem sextus virtus aliquis tamen sanguis nec quattuor ne celer easdem libertus unde unde unde domesticus cuius cui quin
```
KEY: `OXPU6JRO4X`
The `latin.bin` is on the repository
