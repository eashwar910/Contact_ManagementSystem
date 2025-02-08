# Contact Management System

This project is a Contact Management System implemented in C, featuring a login and sign-up system with data validation, sorting, and searching functionalities. The system allows users to store, manage, and organize their contacts efficiently.

## Features

### User Authentication (Login & Sign-Up System)
- **Sign-Up:**
  - Users create an account with a username and password.
  - Password must contain at least 8 characters, including uppercase, lowercase, a digit, and a special character.
  - Usernames must be unique and stored in a `users.csv` file.

- **Login:**
  - Users must enter valid credentials to access their personal contact file.
  - Each user has a separate contact file (e.g., `contact_username.csv`).

### Contact Management
- **Add Contact**  
  - Users can add contacts with name, phone number, and email.  
  - Input data is validated before storing.  

- **Delete Contact**  
  - Contacts can be deleted by name, phone number, or email.  
  - If multiple matches are found, the user can select which contact to delete.  

- **Edit Contact**  
  - Users can edit name, phone number, or email of existing contacts.  
  - Data is validated before updating the contact.  

- **Search Contact**  
  - Users can search by name, phone number, or email.  
  - The search is case-insensitive for better usability.  

- **Sort Contacts**  
  - Contacts can be sorted alphabetically by name or numerically by phone number using Merge Sort.  

- **Display Contacts**  
  - Shows all contacts in a formatted table with color-coded output.  

## How It Works

### Modular Header File Approach
Instead of writing all functions in a single file, the project is structured using a header file (`contacth.h`). This makes the code more organized, reusable, and easier to maintain.

The main file (`contacts.c`) only includes the header file:

```c
#include "contacth.h"
```

All functions related to sorting, validation, login, and contact management are defined in `contacth.c` but declared in `contacth.h`. This modular approach helps separate logic and allows easy expansion.

## Data Validation

The system ensures data integrity through multiple validation checks:

- **Username Validation:**
  - Must be at least 8 characters long.

- **Password Validation:**
  - Must contain uppercase, lowercase, digit, and special character.

- **Email Validation:**
  - Must end with "@gmail.com".

- **Phone Number Validation:**
  - Must start with "+60" (Malaysia) or "+44" (UK).

- **Name Validation:**
  - Must be alphanumeric (no special characters except spaces).

Example validation function:

```c
int validate(char* name_x, char* phone_num_x, char* email_x) {
    if (endswith(email_x, "@gmail.com") == 0) return 0;
    if (!(strncmp(phone_num_x, "+60", 3) == 0 || strncmp(phone_num_x, "+44", 3) == 0)) return 0;
    if (alphanumeric(name_x) == 0) return 0;
    return 1;
}
```

## How to Use

1. Compile the program:
```bash
gcc contacts.c contacth.c -o contact_manager
```

2. Run the executable:
```bash
./contact_manager
```

3. Follow the on-screen menu to sign up, log in, and manage contacts.

## File Structure

```
📁 Contact-Management-System  
│── 📄 contacth.h       # Header file (function declarations & struct definitions)  
│── 📄 contacth.c       # Function implementations (sorting, validation, login, etc.)  
│── 📄 contacts.c       # Main file (user interface & menu system)  
│── 📄 users.csv        # Stores registered usernames & passwords  
│── 📄 contact_<username>.csv  # Individual contact files for each user  
```

## Why This Design?

- **Modular Code** - Organized and maintainable.
- **Efficient Sorting** - Uses Merge Sort for optimal performance.
- **Data Validation** - Prevents incorrect user input.
- **Secure Login System** - Ensures unique user profiles.
- **User-Friendly Interface** - Color-coded output and structured menus.

## Future Improvements

- Add encryption for stored passwords.
- Support more phone number formats globally.
- Implement a GUI version for better usability.

This project is a structured C programming example with a focus on modularity, security, and user-friendly design.

Feel free to contribute!
