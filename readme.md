Certainly! Here’s the updated `README.md` with added tags for better searchability.

---

# C++ Multithreaded File Downloader

## Overview

This project is a C++ multithreaded file downloader that utilizes the cURL library to download a large file in parts concurrently. Each part is downloaded by a separate thread, and the parts are then merged to form the complete file.

## Features

- **Multithreaded Downloading**: Splits the file into multiple parts and downloads them simultaneously.
- **Part Merging**: Merges the downloaded parts into a single file.
- **cURL Integration**: Uses the cURL library for HTTP requests and file downloads.

## Requirements

- **C++ Compiler**: A C++11 compliant compiler.
- **cURL Library**: The cURL library should be installed and linked with your project.

## Clone the Repository

1. **Clone the Repository**:

   ```bash
   git clone https://github.com/kaleharshavardhan07/Multi_thread_File_downloader.git
   ```



## Build the Project

1. **Install cURL**: Ensure cURL is installed on your system. You can download it from [cURL's official website](https://curl.se/download.html).

2. **Compile the Code**: Use the following command to compile the code with g++ (assuming cURL is correctly installed and linked):

   ```bash
   g++ -std=c++11 -o downloader downloader.cpp -lcurl
   ```

   Replace `downloader.cpp` with the name of your source file if different.

## How to Run

1. **Execute the Program**:

   ```bash
   ./downloader
   ```

2. **Input the URL**: Enter the URL of the file you wish to download when prompted.

3. **Specify the File Size**: Enter the total size of the file in bytes.

   - The program will split the file into parts and start downloading each part in a separate thread.
   - After all threads complete, the downloaded parts will be merged into a single file named `largefile.zip`.

## Example

```
ENTER THE LINK ADDRESS: https://example.com/largefile.zip
ENTER THE SIZE OF ZIP FILE: 104857600
```

## Thread Work Diagram

Below is a diagram showing the multithreaded download process:

```
+-----------------+
|     Main Thread |
+-----------------+
        |
        v
+-----------------+                 +-----------------+
|  Thread 1       |                 |  Thread 2       |
|  Download Part  |                 |  Download Part  |
|  (0 - N/4)      |                 |  (N/4 - N/2)    |
+-----------------+                 +-----------------+
        |                                |
        v                                v
+-----------------+                 +-----------------+
|  Thread 3       |                 |  Thread 4       |
|  Download Part  |                 |  Download Part  |
|  (N/2 - 3N/4)   |                 |  (3N/4 - N)     |
+-----------------+                 +-----------------+
        |                                |
        v                                v
+-----------------------------+
|       Merge Parts           |
| (Combine all downloaded     |
|  parts into final file)     |
+-----------------------------+
        |
        v
+-----------------------------+
|     Download Completed      |
+-----------------------------+
```

In the diagram:
- The **Main Thread** initializes and manages the downloading threads.
- **Thread 1** through **Thread 4** each handle downloading a different part of the file.
- After all threads complete, the **Merge Parts** step combines the individual parts into the final file.

## Troubleshooting

- **cURL Initialization Failure**: Ensure that cURL is correctly installed and linked. Check the installation and library paths.
- **File Size Issues**: Make sure to input the correct file size. Incorrect sizes may lead to incomplete downloads or merging errors.

## Tags

- **C++**
- **Multithreading**
- **File Downloader**
- **cURL**
- **Concurrent Download**
- **Threading**
- **HTTP Requests**
- **File Merging**

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---
