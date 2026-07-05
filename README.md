# 🎵 Interactive Smart Playlist Manager

A console-based Smart Interactive Looping Playlist built in **C++** using a **Doubly Circular Linked List**.

## Features

- ▶️ **Next / Previous Song** — Seamless infinite looping in both directions
- ➕ **Add Song** — Dynamically add new songs to the playlist
- ❌ **Delete Song** — Remove any song by index with full edge case handling
- 📋 **View Playlist** — Display all songs in circular order
- 🧹 **Memory Cleanup** — Proper deallocation on exit (no memory leaks)

## Data Structure

Uses a **Doubly Circular Linked List** where:
- `tail->next` points back to `head`
- `head->prev` points back to `tail`
- Enables O(1) forward and backward navigation

## Edge Cases Handled

- Deleting the currently playing song
- Deleting head, tail, or the only remaining node
- Adding to an empty playlist
- Invalid index input validation

## How to Run

```bash
g++ playlist.cpp -o playlist
./playlist
