# ft_irc: A C++98 IRC Server

## Overview

This project implements a core IRC server designed for C++98 compatibility. It utilizes ```poll()``` for efficient, non-blocking input/output management, enabling the server to handle multiple clients simultaneously.

## Key Features

* User authentication with connection passwords
* Channel creation and management
* Private messaging
* Operator privileges and commands:
	* KICK
	* INVITE
	* TOPIC
	* MODE

## Getting Started

1. Compilation:
```make```
2. Execution:
```./ircserv <port> <server_password>```

## Usage
Connect to the server using your preferred IRC client (LimeChat or HexChat for example). Remember to use specified port and password.

## Project Requirements

* Non-blocking I/O using ```poll()```
* Compatibility with any IRC client

## Design

The server's architecture centers around a main loop that leverages ```poll()``` to monitor file descriptors for client connections, incoming data, and outgoing messages. This ensures efficient and scalable handling of multiple clients.
