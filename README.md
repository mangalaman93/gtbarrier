## gtbarrier
Barrier Synchronization Algorithm using OpenMP &amp; OpenMPI

## File Structure
|   file name   |  Implemented Barrier  |
|:-------------:|:---------------------:|
| dbarrier*.cpp | Dissemination Barrier |
| tbarrier*.cpp |   Tournament Barrier  |
| cbarrier*.cpp |  Centralised Barrier  |

where * can be `mp`|`mpi`|`mixed`. The corresponding correctness tests will have `test1_` prefix in the `test` folder. The corresponding performance test will have `perf_` as prefix in the same `test` folder

## How to Run
* run `make` to compile all the code
* all the executables is present in `bin/` folder
* `.pbs` files are provided in the root directory for each `openmp`|`openmpi`|`mixed` barrier codes
* output when .pbs files are excuted, is present in `results` folder

## Resources
* code: https://github.com/mangalaman93/gtbarrier
* data: https://docs.google.com/spreadsheets/d/1qVHuFdnH7InjpncFwjebgAO-8SEiGdRbnZxBpLchLlc
* report: doc/README.pdf, doc/report.pdf
