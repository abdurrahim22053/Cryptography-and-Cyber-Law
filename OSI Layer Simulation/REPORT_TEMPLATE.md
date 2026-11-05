# Project Report: OSI Layer Simulation – Live Project

## 1. Abstract
This project demonstrates a seven-layer OSI model using C-based client and server applications connected through real TCP sockets. The application-level simulation illustrates encapsulation at the sender and decapsulation at the receiver. A Python Tkinter dashboard presents the layer progression and checkpoints after every two layers.

## 2. Objectives
- Understand the responsibilities of all seven OSI layers.
- Implement client-server communication using TCP sockets in C.
- Demonstrate the conceptual encapsulation/decapsulation process.
- Visualize layer progression through a Python interface.
- Distinguish simulated OSI stages from actual TCP/IP stack operations.

## 3. Problem Statement
Students often learn OSI layers as theory and find it difficult to visualize how data moves between sender and receiver. This project provides an interactive demonstration that combines a real socket transfer with educational layer-by-layer processing logs.

## 4. Methodology
1. User enters text in the Python GUI.
2. Python launches the C client.
3. Client logs simulated L7→L1 encapsulation.
4. Client sends a length-prefixed message using TCP.
5. C server receives the message.
6. Server logs simulated L1→L7 decapsulation.
7. Server returns an acknowledgement.
8. Python dashboard displays progress and completion.

## 5. Technologies
C, POSIX TCP sockets, Python 3, Tkinter, GCC, Ubuntu/WSL.

## 6. Testing
| Test | Input/Action | Expected Result |
|---|---|---|
| Local message | `Hello Server!` | Server prints received message; client ACK |
| Empty GUI message | Blank text | GUI warns user |
| Wrong port | Port 9999 without server | Client connection error |
| Long message | More than 4096 bytes | Client rejects message |
| Repeat messages | Send several times | Server accepts each connection |

## 7. Results
Record screenshots of: server listening terminal, GUI before sending, GUI progress checkpoints, server received message, successful ACK.

## 8. Limitations
The L5, L6, L2, and L1 stages are educational representations implemented in application space. Actual transmission is performed by the host TCP/IP stack. The code does not create raw Ethernet frames or modify Linux kernel networking.

## 9. Conclusion
The project demonstrates how a message can be modeled across the OSI layers while being delivered through real TCP socket communication. The visualizer improves understanding of encapsulation, decapsulation, and client-server networking.

## 10. Future Enhancements
- Add packet capture integration using Wireshark.
- Add multiple clients using threads/select.
- Add detailed header fields and checksum demonstrations.
- Add GUI animation and receiver-side visualization.
