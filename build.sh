#!/bin/bash

# Function to print messages
print_message() {
    echo "==> $1"
}

# Function to check for required tools
check_requirements() {
    local missing_tools=()
    
    # Check for CMake
    if ! command -v cmake &> /dev/null; then
        missing_tools+=("cmake")
    fi
    
    # Check for C++ compiler
    if [[ "$OS" == "Windows_NT" ]]; then
        if ! command -v cl &> /dev/null; then
            missing_tools+=("MSVC")
        fi
    else
        if ! command -v g++ &> /dev/null && ! command -v clang++ &> /dev/null; then
            missing_tools+=("g++/clang++")
        fi
    fi
    
    # Check for SQLite3
    if ! command -v sqlite3 &> /dev/null; then
        missing_tools+=("sqlite3")
    fi
    
    if [ ${#missing_tools[@]} -ne 0 ]; then
        print_message "Error: Missing required tools: ${missing_tools[*]}"
        print_message "Please install the missing tools and try again."
        exit 1
    fi
}

# Function to install dependencies
install_dependencies() {
    case "$1" in
        "Linux")
            if command -v apt-get &> /dev/null; then
                print_message "Installing dependencies using apt..."
                sudo apt-get update
                sudo apt-get install -y build-essential cmake libsqlite3-dev
            elif command -v dnf &> /dev/null; then
                print_message "Installing dependencies using dnf..."
                sudo dnf install -y gcc-c++ cmake sqlite-devel
            elif command -v pacman &> /dev/null; then
                print_message "Installing dependencies using pacman..."
                sudo pacman -Sy gcc cmake sqlite
            else
                print_message "Warning: Unsupported package manager. Please install dependencies manually."
            fi
            ;;
            
        "Darwin") # macOS
            if command -v brew &> /dev/null; then
                print_message "Installing dependencies using Homebrew..."
                brew install cmake sqlite3
            else
                print_message "Installing Homebrew..."
                /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
                brew install cmake sqlite3
            fi
            ;;
            
        "Windows_NT")
            print_message "On Windows, please ensure you have:"
            print_message "1. Visual Studio with C++ tools installed"
            print_message "2. CMake installed and added to PATH"
            print_message "3. SQLite3 installed and added to PATH"
            read -p "Press Enter to continue if you have all requirements..."
            ;;
            
        *)
            print_message "Unsupported operating system"
            exit 1
            ;;
    esac
}

# Function to build the project
build_project() {
    print_message "Creating build directory..."
    mkdir -p build
    cd build || exit
    
    print_message "Configuring project with CMake..."
    if [[ "$OS" == "Windows_NT" ]]; then
        cmake -G "Visual Studio 16 2019" -A x64 ..
        
        print_message "Building project..."
        cmake --build . --config Release
    else
        cmake ..
        
        # Get number of CPU cores for parallel build
        if [[ "$OSTYPE" == "darwin"* ]]; then
            cores=$(sysctl -n hw.ncpu)
        else
            cores=$(nproc)
        fi
        
        print_message "Building project using $cores cores..."
        cmake --build . -j "$cores"
    fi
}

# Function to run tests if they exist
run_tests() {
    if [ -f "tests/shop_tests" ]; then
        print_message "Running tests..."
        ./tests/shop_tests
    fi
}

# Main script execution
main() {
    # Detect operating system
    if [[ "$OSTYPE" == "darwin"* ]]; then
        OS="Darwin"
    elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
        OS="Linux"
    elif [[ "$OS" == "Windows_NT" ]]; then
        OS="Windows_NT"
    else
        print_message "Unsupported operating system: $OSTYPE"
        exit 1
    fi
    
    print_message "Detected operating system: $OS"
    
    # Check for required tools
    check_requirements
    
    # Install dependencies
    install_dependencies "$OS"
    
    # Build project
    build_project
    
    # Run tests
    run_tests
    
    print_message "Build process completed!"
    
    # Print run instructions
    if [[ "$OS" == "Windows_NT" ]]; then
        print_message "You can find the executable at: build\\Release\\shop_exe.exe"
    else
        print_message "You can find the executable at: build/shop_exe"
    fi
}

# Execute main function
main