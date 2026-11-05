# OSI Layer Simulation – Live Project

A teaching-oriented, application-level simulation of the seven OSI layers, backed by real TCP socket communication between C client and C server. A Python Tkinter dashboard visualizes encapsulation, transmission, decapsulation, and progress after each pair of layers.

> This project simulates OSI layer behavior in user space. It does not modify the Linux kernel or claim that TCP/IP implements seven separate OSI protocols.

## Features
- C TCP server and client (POSIX sockets; Ubuntu/Linux/WSL)
- Explicit seven-stage encapsulation and decapsulation simulation
- Real TCP socket transmission of a framed JSON-like text message
- Python Tkinter GUI with zig-zag flow, event log, progress, and send controls
- Pair-of-layers progress checkpoints (2/7, 4/7, 6/7, 7/7)
- Basic input validation, socket error handling, and length-prefixed payload
- Build/run instructions and viva questions

## Requirements
- Ubuntu 22.04+ or WSL Ubuntu
- GCC, make, Python 3
- Tkinter (`sudo apt install python3-tk`)

## Build
```bash
cd OSI_Layer_Simulation_Project
make
```

## Run (two terminals)
Terminal 1:
```bash
./osi_server 127.0.0.1 5050
```
Terminal 2:
```bash
./osi_client 127.0.0.1 5050 "Hello Server!"
```
The C client/server print simulated layer steps and transfer data over TCP.

## Run GUI
Start the server first, then:
```bash
python3 visualizer.py
```
Enter server IP/port and a message, then click **Send through OSI**. The GUI launches the C client, captures its layer logs, and displays a live-ish event sequence. For GUI testing, keep the server running.

## Demo plan
1. Start server and show `LISTENING`.
2. Start GUI and enter `Hello from Rahim`.
3. Press Send; point out checkpoints 2/7, 4/7, 6/7, 7/7.
4. Show server terminal receiving the payload.
5. Explain simulated OSI wrappers versus actual TCP/IP socket stack.

## Architecture
- `client.c`: constructs simulated encapsulation headers, sends framed payload via TCP.
- `server.c`: reads length-prefixed message, prints decapsulation stages, sends ACK.
- `osi_common.h`: shared frame format and helpers.
- `visualizer.py`: Tkinter dashboard; invokes C client and interprets progress output.
- `Makefile`: builds both programs.

## Limitations / honest scope
- Presentation, Session, Data Link, and Physical are educational simulations in application space.
- TCP/IP kernel networking performs actual transport/network/link handling.
- The application-level frame is a simple length-prefixed teaching protocol, not an Ethernet/IP packet capture.
