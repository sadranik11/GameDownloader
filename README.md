# Game Downloader

A simple Windows-based downloader application built with **C++** and **Qt**, designed to download multiple files (e.g., game assets) with support for pausing/resuming, uninstalling, and checking file integrity.

---

## Features

- **Start Download**: Begins downloading a predefined list of files.
- **Pause/Resume**: Temporarily interrupts or resumes the current download session.
- **Uninstall**: Deletes all previously downloaded files and resets the UI to its original state.
- **File Integrity Checker**: Scans downloaded files and offers redownload options for any missing or corrupted files.
- **Progress Tracking**: Displays real-time download progress in megabytes and percentage.
- **UI Control Flow**:
  - `Pause/Resume` and `Uninstall` buttons are **disabled** at launch.
  - These buttons are **enabled** after pressing `Start Download`.
  - Once all files are downloaded, `Pause/Resume` is disabled again.
  - After using `Uninstall`, everything resets to the initial state for cleanliness and bug prevention.

---

## Screenshot

![Screenshot](assets/Screenshot.png)

---

## Installation

> **Note**: This app is designed and tested for **Windows 11**.

1. Clone the repository:
   ```bash
   git clone https://github.com/sadranik11/GameDownloader.git
   ```
2. Open the `.pro` file in **Qt Creator** (Tested with Qt 6.x).
3. Build and Run the project.

---

## How it Works

- The application contains a list of URLs (currently 4 PNG images from Imgur).
- On clicking `Start Download`, files are downloaded one by one and stored in a chosen folder under a subdirectory called `Game files`.
- If the download is paused, it stores the byte progress and uses HTTP range requests to resume.
- `Uninstall` removes all downloaded files and cleans up the folder.

---

## License

This project is shared under the **MIT License**, since it uses the free version of Qt and contains no commercial dependencies.

---

## Notes

- **Pause/Resume** uses `abort()` to stop download and resumes with `Range` headers.
- **Download integrity** is ensured via file size and existence checks.
- No threading is used; all operations are based on Qt’s asynchronous networking.

---

## Contact

Built with love by [Sadra Nik](https://github.com/sadranik11)  
You can check out more on my GitHub page!

