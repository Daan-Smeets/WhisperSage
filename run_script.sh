make PLATFORM=cw308t-stm32f3 IMPLEMENTATION_PATH=crypto_kem/kyber768/m4fmasked bin/crypto_kem_kyber768_m4fmasked_test.bin
openocd -f interface/stlink-v2-1.cfg -f target/stm32f3x.cfg -c "program bin/crypto_kem_kyber768_m4fmasked_test.bin 0x08000000 verify reset exit"