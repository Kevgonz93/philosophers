# Testing with LPT

```bash
git clone https://github.com/MichelleJiam/LazyPhilosophersTester
cd LazyPhilosophersTester
./test.sh
```

## Obtenemos este error que, creo, se podría cambiar. TEnemos que revisar si aceptamos un philo o en la validación detenemos el flujo del programa.

Test: [1 800 200 200] | a philo should die

Press ENTER to start test, press any other key to exit tester...

Error: time to die invalid

--- 

## Manteniendo la espera en "To_think" obtenemos un error:

### Test: [4 410 200 200] | no one should die

Press ENTER to start test, press any other key to exit tester...

[                                                  ] 0% (0 / 15 seconds)

KO - program terminated prematurely

---

## Tras quitar la espera en "to_think" obtenemos estos errores:


### Test: [5 800 200 200] | no one should die

Press ENTER to start test, press any other key to exit tester...

[###############                                   ] 30% (3 / 10 seconds)

KO - program terminated prematurely

### Test: [5 600 150 150] | no one should die

Press ENTER to start test, press any other key to exit tester...

[#########################                         ] 50% (5 / 10 seconds)

KO - program terminated prematurely

### Test: [4 410 200 200] | no one should die

Press ENTER to start test, press any other key to exit tester...

[##################################################] 100% (10 / 10 seconds)

OK
Terminated
SIGTERM: no process found

### Test: [100 800 200 200] | no one should die

Press ENTER to start test, press any other key to exit tester...

[##################################################] 100% (10 / 10 seconds)

OK
SIGTERM: no process found
Terminated

### Test: [105 800 200 200] | no one should die

Press ENTER to start test, press any other key to exit tester...

[##################################################] 100% (10 / 10 seconds)

OK
SIGTERM: no process found
Terminated

### Test: [200 800 200 200] | no one should die

Press ENTER to start test, press any other key to exit tester...

[##################################################] 100% (10 / 10 seconds)

OK
SIGTERM: no process found

No-Die Tests: PASSED: 4/6 | FAILED: 2/6
