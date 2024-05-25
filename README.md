# How to build

```sh
git clone https://github.com/khadievedem/sw-architecture-lab.git && cd sw-architecture-lab
git switch eco/lab4
mkdir -p BuildFiles/STM32/arm-gcc
pushd AssemblyFiles/STM32/arm_gcc
make -f Makefile
make -f MakefileExe
popd
```
