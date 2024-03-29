# How to run

```sh
git clone https://github.com/khadievedem/sw-architecture-lab.git && cd sw-architecture-lab
mkdir -p BuildFiles/EcoLab1
cp -r <path-to-insideACOM>/insideACOM/001.InsideACOM/Lessons/* ./BuildFiles/
cp -r <path-to-EcoLab1>/BuildFiles/Linux/x64/* ./BuildFiles/EcoLab1
pushd AssemblyFiles/Linux/gcc_7_4_0/
chmod +x build.sh && ./build.sh && popd
cd BuildFiles/Linux/x64/StaticDebug
./EcoLab2
```
