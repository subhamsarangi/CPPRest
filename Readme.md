# Setting Up a C++ REST API with cpprestsdk

## Install Required Packages
Install essential tools
```bash
sudo apt install cmake
sudo apt-get install libssl-dev
sudo apt-get install curl zip unzip tar  
```
Install the `cpprestsdk` library for building REST APIs.
```bash
sudo apt-get install libcpprest-dev        
```

## Clone vcpkg Repository
Clone the `vcpkg` package manager from GitHub.
```bash
git clone https://github.com/microsoft/vcpkg.git  
```

## Bootstrap vcpkg
Run the bootstrap script to install `vcpkg`.
```bash
./vcpkg/bootstrap-vcpkg.sh  
```

## Install cpprestsdk
Use `vcpkg` to install the `cpprestsdk` library. [_TAKES SOME TIME!_]
```bash
./vcpkg/vcpkg install cpprestsdk  
```
List installed packages to verify the installation.
```bash
./vcpkg/vcpkg list                 
```

## Project Structure
Create a directory structure for your C++ REST API project.
```
/cpprest_example
├── main.cpp                        
├── CMakeLists.txt                 
```

## Build the Project
Create a build directory and navigate into it.
```bash
mkdir build && cd build           
```
Generate build files with CMake.
```bash
cmake ..                          
```
Compile the project using Make.
```bash
make                              
```

## Run the Application
Execute the compiled REST API application.
```bash
./cpprest_example                  
```

## Test the API with curl
Retrieve all items from the API.
```bash
curl http://localhost:8080/api/items  
```
- Not implemented yet.
Create a new item in the API.
```bash
curl -X POST http://localhost:8080/api/items -H "Content-Type: application/json" -d "{\"name\": \"New Item\"}"
```
Delete an item with ID 1 from the API.
```bash
curl -X DELETE http://localhost:8080/api/items/1
``` 