# Pocket-Git

A minimal Git implementation in C++03, built for educational purposes and as preparation for contributing to [CERN-HSF cvmfs](https://github.com/cvmfs/cvmfs).

## Overview

Pocket-Git implements core Git functionality from scratch, providing insight into Git's internal object model, compression strategies, and command-line interface design. The project adheres strictly to C++03 standards and follows cvmfs coding conventions.

Unlike standard Git which uses SHA-1 hashing, pocket-git uses SHA-256 for object identification.

## Architecture

The codebase follows a three-layer architecture mirroring patterns used in cvmfs:

```
src/
├── core/          Object model and repository abstractions
│   ├── object.h/cc         Abstract base class for Git objects
│   ├── blob_object.h/cc    File content storage
│   ├── tree_object.h/cc    Directory structure representation
│   ├── commit_object.h/cc  Commit metadata and history
│   ├── repository.h/cc     Repository initialization and management
│   └── index.h/cc          Staging area implementation
├── commands/      CLI command handlers
│   ├── init.h/cc           Initialize repository
│   ├── hash_object.h/cc    Compute and store object hashes
│   ├── cat_file.h/cc       Inspect object contents
│   ├── add.h/cc            Stage file changes (planned)
│   └── commit.h/cc         Create commits (planned)
└── utils/         Low-level utilities
    ├── hash_utils.h/cc     SHA-256 hashing via OpenSSL
    ├── compression.h/cc    Zlib compression/decompression
    ├── file_utils.h/cc     POSIX file operations
    └── string_utils.h/cc   String manipulation helpers
```

## Dependencies

- **zlib**: Object compression and decompression
- **OpenSSL libcrypto**: SHA-256 hashing
- **POSIX APIs**: File system operations (no C++11 std::filesystem)
- **g++**: C++03 compliant compiler

On Debian/Ubuntu systems:

```bash
apt-get install zlib1g-dev libssl-dev build-essential
```

## Building

pocket-git uses direct compilation without a build system:

```bash
g++ -std=c++03 -Wall -Wextra -o pocket-git \
    src/main.cpp \
    src/commands/*.cc \
    src/core/*.cc \
    src/utils/*.cc \
    -lz -lssl -lcrypto
```

## Usage

### Initialize a Repository

```bash
./pocket-git init [path]
```

Creates a new Git repository structure at the specified path (defaults to current directory). Initializes `.git` directory with standard subdirectories: `objects/`, `refs/`, `HEAD`.

**Example:**

```bash
./pocket-git init my-repo
# Initialized pocket-git repository in /path/to/my-repo/.git
```

### Compute Object Hash

```bash
./pocket-git hash-object [-w] [--stdin] <file>
```

Computes the SHA-256 hash of a file as a Git blob object. Optionally writes the object to the repository database.

**Flags:**
- `-w`: Write the object to `.git/objects/` database
- `--stdin`: Read content from standard input instead of a file

**Examples:**

```bash
# Compute hash without storing
./pocket-git hash-object README.md
# a3f58fb291c5d2e1b4c9d8e7f6a5b4c3d2e1f0a9b8c7d6e5f4a3b2c1d0e9f8a7

# Store object in database
./pocket-git hash-object -w README.md

# Hash content from stdin
echo "Hello, Git!" | ./pocket-git hash-object --stdin
```

### Inspect Objects

```bash
./pocket-git cat-file (-p|-t|-s|-e) <hash>
```

Retrieves and displays information about stored objects from the repository database.

**Flags (Optional):**
- `-p`: Pretty-print object contents
- `-t`: Show object type (blob, tree, commit)
- `-s`: Show object size in bytes
- `-e`: Check if object exists (exit code only)

**Examples:**

```bash
# View object contents
./pocket-git cat-file -p a3f58fb291c5

# Check object type
./pocket-git cat-file -t a3f58fb291c5
# blob

# Get object size
./pocket-git cat-file -s a3f58fb291c5
# 1234
```

## Implementation Status

**Implemented:**
- Repository initialization (`init`)
- Object hashing and storage (`hash-object`)
- Object inspection and retrieval (`cat-file`)
- Blob object model with compression
- SHA-256 hashing infrastructure
- Zlib compression utilities

**In Progress:**
- Staging area and index management (`add`)
- Commit creation and metadata (`commit`)
- Tree object traversal
- Reference management

**Planned:**
- Branch operations
- Merge functionality
- Diff algorithms
- Remote operations (fetch/push)

## Code Conventions

This project strictly follows cvmfs coding standards:

- **Standard**: C++03 only (no C++11 features)
- **Indentation**: 2 spaces, 80 character line limit
- **Braces**: Opening brace on new line
- **Naming**:
  - Classes/Functions: `CamelCase`
  - Variables: `snake_case`
  - Class members: `snake_case_` (trailing underscore)
  - Constants: `kCamelCase`
- **Constructors**: No work in constructors, use explicit `Init()` methods
- **Header guards**: `PROJECT_PATH_FILE_H_` format

## Educational Purpose

pocket-git serves as a learning tool for understanding:

- Git's content-addressable object database
- Delta compression and storage optimization
- Directed acyclic graph (DAG) structures for version history
- POSIX file system APIs and low-level I/O
- C++03 patterns and memory management
- Large-scale C++ project conventions used in scientific computing

This implementation intentionally avoids modern conveniences (C++11, external frameworks) to match the constraints of cvmfs and similar legacy codebases in high-energy physics computing environments.

## License

This project is intended for educational purposes.

## References

- [CERN-HSF cvmfs](https://github.com/cvmfs/cvmfs)
