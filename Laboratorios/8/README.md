## Integrantes:

B82957 : Marco Ferraro Rodriguez
B86524 : Gabriel Revillat Zeledon

## Resultados:

###  n = 10000000

| Exercise | num_processes | time elapsed |
|----------|---------------|--------------|
| count_primes_process | 1 | 11.3044s |
| count_primes_process | 16 | 8.25016s |
| count_primes_process | 32 | 8.60682s |
| count_primes_process | 64 | 9.30445s |
| count_primes_reduction | 1 | 11.5267s |
| count_primes_reduction | 16 | 13.0768s |
| count_primes_reduction | 32 | 12.5417s |
| count_primes_reduction | 64 | 14.2736s |
| count_primes_all_reduce | 1 | 11.3377s |
| count_primes_all_reduce | 16 | 3.82539s |
| count_primes_all_reduce | 32 | 3.14027s |
| count_primes_all_reduce | 64 | 2.24348s |