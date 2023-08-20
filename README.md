# UDP Socket Chat 🗣️

udp-socket-chat is a simple UDP client and server implementation using socket programming in C. This project provides practice in working with sockets, understanding networking concepts, and getting familiar with the UDP transport protocol.

## Table of Contents

- [Features](#features)
- [Dependencies](#dependencies)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Features ✨

- UDP client and server written in C
- Offers a simple chat system using UDP sockets
- Server listens on port 9000 for incoming messages
- Server replies to client messages with the current system time and date
- Great for learning and understanding socket programming and the UDP transport protocol

## Dependencies 📚

- A C compiler (such as GCC) and a Unix-based system (Linux, macOS, etc.) with standard C libraries

## Installation ⚙️

1. Clone this repository:

   `git clone https://github.com/zulfkhar00/udp-socket-chat.git`

2. Compile both client and server programs using the provided Makefile:

   ```
   cd udp-socket-chat
   make all
   ```

3. This will create two executables: `./client` and `./server`.

## Usage 🚀

Both the client and server programs should be run from two different terminal windows.

1. First, run the server program in one terminal:

   `./server`

   The server will open a UDP socket, listen on port 9000 for incoming messages, and reply to any message received from a client with the current system time and date. The server will also print a message for every incoming message, indicating the message has been received, and indicating the IP address and port number from which it was received.

2. In another terminal window, run the client program:

   `./client`

   The client program will open a UDP socket, send a meaningful message (e.g., "Time request") to the server on port 9000, and wait for a reply from the server. The reply from the server (i.e., the current time and date of the server) will be printed on the terminal in a readable format.

## Contributing 🤝

1. Fork the Repository

2. Clone your fork

3. Create your feature branch (`git checkout -b feature/AmazingFeature`)

4. Commit your changes (`git commit -m 'Add some AmazingFeature'`)

5. Push to the branch (`git push origin feature/AmazingFeature`)

6. Open a Pull Request

## License 📄

This project is licensed under the MIT License. Please see the [LICENSE](LICENSE) file for more details.
