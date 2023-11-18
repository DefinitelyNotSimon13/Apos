# Apos - Database Manager

Developed by Simon Blum, Apos - Database Manager is a comprehensive Windows
application designed to manage SQLite3 databases.

The application provides an intuitive and user-friendly interface for performing
a variety of database operations. Whether you need to open, read, edit tables,
or execute custom SQLite3 commands, Apos - Database Manager has got you covered.

The name "Apos" is inspired by the ancient Greek word "αποθήκη", which translates
to "storage" or "warehouse".

## Key Features

- **Efficient Database Operations**: Open, read, and edit tables within SQLite3
  databases with ease.
- **Custom SQLite3 Commands**: Execute custom SQLite3 commands for advanced
  database operations.
- **Intuitive User Interface**: Navigate through the application effortlessly
  with the GUI, built using the Qt framework.

## Prerequisites

- Windows Operating System

## Installation

To install Apos - Database Manager, follow these steps:

1. Navigate to the [Releases](https://github.com/DefinitelyNotSimon13/Apos/releases) page.
2. Download the latest installer.
3. Run the installer and follow the on-screen instructions.

## Usage

1. **Opening a Database**: Launch the application and click on the "Open Database"
   button to select the desired SQLite3 database file.
2. **Executing Commands**: Enter custom SQLite3 commands in the "Command Box"
   and click the "Execute" button.
3. **Managing Tables**: Use the GUI to perform various table operations such as
   "Add," "Update," and "Select Table".

## Project Structure

The project is organized into several directories:

- `/source`: Contains the main entry point for the application (`main.cpp`).
- `/classes/backendClasses`: Contains classes related to the backend logic of
  the application, such as `StartupHandler` and `ObjectHandler`.
- `/classes/frontendClasses`: Contains classes related to the frontend logic of
  the application, such as `WindowHandler` and various window classes.
- `/classes/databaseClasses`: Contains classes related to database operations,
  such as `DatabaseHandler` and `TableHandler`.
- `/resources`: Stores additional resources used by the application, such as
  translation files and the application logo.
- `/docs`: Contains the Doxygen-generated documentation for the project.

## Documentation

Comprehensive documentation for Apos - Database Manager is available on the
[GitHub Pages website](https://definitelynotsimon13.github.io/Apos/) and in
the `/docs` directory of this repository.

## Contributing

As a solo developer, I welcome contributions to the project! Please refer to
the [Contribution Guidelines](CONTRIBUTING.md) for details.

## License

Apos - Database Manager is licensed under the [LGPL-3.0 License](LICENSE.md).

## Acknowledgments

- A big thank you to the Qt framework community for their invaluable resources
  and support.
- [Any other acknowledgments or credits]