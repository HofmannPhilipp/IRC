*This project has been created as part of the 42 curriculum by phhofman, cwolf.*

# ft_irc

## Description

ft_irc is a network programming project focused on implementing a
simplified Internet Relay Chat (IRC) server from scratch.

The goal of the project is to understand low-level networking concepts,
socket communication, multiplexing, and concurrent client handling. The
server is designed to support multiple clients simultaneously while
maintaining responsive and efficient communication.

The implementation was written in C++ (C++17) and emphasizes
non-blocking I/O to ensure that no single client can block the entire
server. The poll() system call is used for event-driven socket
management, enabling scalable handling of multiple connections.

Key aspects of the project include:

-   TCP socket programming
-   Event-driven architecture using poll()
-   Non-blocking client communication
-   Command parsing and protocol handling
-   Basic IRC channel and user management

The server supports several IRC modes, including:

-   i (invite-only)
-   t (topic restrictions)
-   k (channel key)
-   o (operator privileges)
-   l (user limit)

------------------------------------------------------------------------

## Instructions

### Compilation

The project is built using a C++17-compatible compiler.

Example with g++:

``` bash
c++ -Wall -Wextra -Werror -std=c++17 *.cpp -o ircserv
```

(Adapt file names as needed depending on your project structure.)

------------------------------------------------------------------------

### Execution

``` bash
./ircserv <port> <password>
```

Example:

``` bash
./ircserv 6667 mypassword
```

The server will start listening for incoming IRC client connections on
the specified port.

------------------------------------------------------------------------

## Technical Choices

### Non-Blocking Design

The server is implemented using non-blocking sockets to prevent clients
from stalling the main event loop. This design ensures that the server
remains responsive even under multiple simultaneous connections.

### poll() for Multiplexing

The poll() system call was chosen for I/O multiplexing. It allows
monitoring multiple file descriptors efficiently and fits well with an
event-driven server architecture.

### C++17

C++17 was used to benefit from modern language features, improved type
safety, and clearer abstractions while still working close to the system
level.

------------------------------------------------------------------------

## Resources

Classic references and learning materials used during the project:

-   RFC 1459 -- Internet Relay Chat Protocol
-   Beej's Guide to Network Programming
-   General socket programming tutorials

Helpful videos for understanding sockets and networking:

-   https://www.youtube.com/watch?v=D26sUZ6DHNQ
-   https://www.youtube.com/watch?v=XXfdzwEsxFk
-   https://www.youtube.com/watch?v=rW_NV6rf0rM

------------------------------------------------------------------------

### AI Usage Disclosure

AI tools were used during the development process for learning and
assistance, specifically for:

-   Understanding server architecture and design strategies
-   Clarifying networking concepts and poll()-based event loops
-   Improving and refining error messages for IRC commands

AI was used as a learning aid and reference tool.

------------------------------------------------------------------------

## Notes

This project was developed as part of the 42 curriculum and follows its
educational constraints and objectives.
