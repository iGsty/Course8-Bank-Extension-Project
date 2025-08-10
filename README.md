# Bank Management System (C++)

## 📌 Overview
This is a **Console-Based Bank Management System** written in **C++** that allows bank staff to manage clients, users, and transactions.  
The system supports **file-based storage**, user authentication with permission control, and various operations such as deposits, withdrawals, and client/user management.

---

## 🚀 Features
### 🔐 Authentication & Permissions
- Login system with username and password.
- Permission-based access control (full access or custom permissions).
- Permission types:
  - View client list
  - Add client
  - Delete client
  - Update client
  - Find client
  - Perform transactions
  - Manage users

### 👤 Client Management
- **List all clients** with account details.
- **Add new clients**.
- **Delete clients** (soft delete, then save to file).
- **Update client information**.
- **Search for a client** by account number.

### 👥 User Management
- **List all users**.
- **Add new users** with specific permissions.
- **Delete users** (except the Admin).
- **Update user details** (password and permissions).
- **Search for users** by username.

### 💰 Transactions
- Deposit money into client accounts.
- Withdraw money from client accounts.
- Display total balance of all clients.

---

## 📂 File Storage
The system uses **text files** to store data:
- **Clients.txt** → Stores client information in the format:
  ```
  AccountNumber#//#PinCode#//#Name#//#Phone#//#Balance
  ```
- **UsersC8.txt** → Stores user login data and permissions:
  ```
  Username#//#Password#//#PermissionValue
  ```

---

## 🖥️ How It Works
1. **Login** using a valid username and password.
2. Based on your **permissions**, the main menu will allow you to:
   - Manage clients
   - Perform transactions
   - Manage users
3. All changes are saved **directly to the files**.

---

## 📜 Example Main Menu
```
===========================================
        Bank Management System
===========================================
[1] Show Client List
[2] Add New Client
[3] Delete Client
[4] Update Client
[5] Find Client
[6] Transactions
[7] Manage Users
[8] Logout
===========================================
```

---

## 🛠️ Technologies Used
- **C++ Standard Library**
  - `<iostream>` for input/output
  - `<fstream>` for file handling
  - `<vector>` for dynamic data storage
  - `<string>` for string manipulation
  - `<iomanip>` for formatted output
- **File-Based Persistence** for data storage.

---

## 📦 Installation & Usage
1. **Clone this repository**
   ```bash
   git clone https://github.com/YourUsername/BankManagementSystem.git
   cd BankManagementSystem
   ```
2. **Compile the program**
   ```bash
   g++ main.cpp -o BankSystem
   ```
3. **Run the program**
   ```bash
   ./BankSystem
   ```

---

## 📌 Notes
- The **Admin** account cannot be deleted.
- A permission value of **-1** means full access.
- Deleted clients/users are removed from the file upon saving.

---

## 📄 License
This project is licensed under the MIT License – feel free to use and modify it.

---

💡 *Built as a C++ project for practicing file handling, user authentication, and structured programming.*
