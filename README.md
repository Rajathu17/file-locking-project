Here’s a detailed explanation for a README file tailored to the program:

---

# **File Lock System**

## **Overview**
The File Lock System is a GUI-based application built using the GTK library in C. It provides administrators with the ability to lock files, set files to read-only mode, and view an audit log of actions. This program is designed to add an additional layer of control over file access and management.

---

## **Features**
1. **Admin Authentication**:
   - Only authorized administrators can access the system.
   - Credentials are verified through a login interface.

2. **File Operations**:
   - **Lock File**: Secure a file to prevent modifications or deletions.
   - **Read-Only Mode**: Restrict a file to read-only access.
   - **View Audit Log**: Display a log of actions performed for monitoring purposes.

3. **User-Friendly Interface**:
   - Simple and intuitive GUI for all operations.
   - Input fields with placeholders for guidance.

---

## **Prerequisites**
- **System Requirements**:
  - Linux or any system with GTK library support.
  - GTK 3+ installed on the system.

- **Dependencies**:
  - C Compiler (e.g., GCC).
  - GTK development libraries (install via `sudo apt install libgtk-3-dev` on Debian-based systems).

---

## **Installation**
1. Clone or download the repository.
2. Compile the program using the following command:
   ```bash
   gcc file_lock_system.c -o file_lock_system `pkg-config --cflags --libs gtk+-3.0`
   ```
3. Run the program:
   ```bash
   ./file_lock_system
   ```

---

## **Usage**
### **Step 1: Admin Login**
- Launch the program.
- Enter the admin username and password.
  - Default credentials:  
    - **Username**: `admin`  
    - **Password**: `password`

### **Step 2: File Operations**
- Upon successful login, a new window will open with the following options:
  - **Lock File**:
    - Enter the name of the file you wish to lock.
    - Click the "Lock File" button.
  - **Read-Only Mode**:
    - Enter the name of the file you wish to set to read-only.
    - Click the "Read-Only Mode" button.
  - **View Audit Log**:
    - Click the "View Audit Log" button to display the contents of `audit_log.txt`.

---

## **Security Notes**
- **Authentication**:
  - Admin credentials are currently hardcoded in the source code.
  - For better security, replace hardcoded credentials with encrypted storage or use environment variables.
- **File Name Validation**:
  - Ensure input file names do not contain malicious characters.
- **Audit Log**:
  - Logs are stored in plain text; consider encrypting the log file for better security.

---

## **Known Issues**
1. **System Call Vulnerabilities**:
   - File operations use `system()` calls, which could be exploited with malicious inputs.
2. **Hardcoded Credentials**:
   - Username and password are stored in the source code.
3. **Limited Error Handling**:
   - The program does not confirm whether external commands execute successfully.

---

## **Future Enhancements**
- **Improved Security**:
  - Replace `system()` with safer alternatives like library calls.
  - Implement secure storage for credentials.
- **Better Error Handling**:
  - Validate return codes for external commands.
  - Provide detailed feedback to the user.
- **Enhanced Logging**:
  - Use GUI to display logs in a user-friendly format.

---

## **Credits**
Developed using GTK and C to provide basic file security functionalities for administrators.

--- 

This README provides all necessary details for installation, usage, security, and future improvements, making it comprehensive for developers and end-users.
