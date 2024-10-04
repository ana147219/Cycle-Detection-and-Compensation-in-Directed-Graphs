# Cycle Detection and Compensation in Directed Graphs

## Project Description:
This project implements **cycle detection** and **compensation calculation** in directed graphs using **C**. The graph structure is represented using an adjacency matrix, and the program provides functionalities for adding and removing nodes and edges, detecting cycles, and calculating the maximum possible compensation within the cycles.

The project offers a menu-based system allowing users to interact with the graph, perform operations, and visualize the results. The stack is used to keep track of visited nodes during the depth-first search (DFS) cycle detection algorithm.

## Features:
- **Graph Operations**:
  - Add or remove nodes
  - Add or remove edges with associated weights
  - Print the entire graph
- **Cycle Detection**:
  - Find and display all cycles in the graph
  - Calculate the maximum compensation within each cycle
- **Compensation Calculation**:
  - Modify the graph by reducing edge weights based on the maximum compensation found in the cycles
- **File Input**:
  - Load graph data from a file for easier testing and demonstration
- **Menu-driven Interface**:
  - Simple console-based menu for performing all operations

## Technologies Used:
- **C**: The entire project is implemented in C.
- **Data Structures**: The graph is represented using an adjacency matrix, and stack-based depth-first search (DFS) is used for cycle detection.

## Code Overview:
- **Graph Representation**: The graph is stored as an adjacency matrix, with each edge assigned a weight.
- **Stack Implementation**: A custom stack is used for tracking nodes during DFS.
- **Cycle Detection**: The DFS algorithm is used to detect cycles, and the minimum edge weight in the cycle is treated as the "maximum compensation."
- **Graph Modification**: After detecting a cycle, the program can adjust edge weights by subtracting the compensation value, effectively "resolving" the cycle.

## How to Run:
1. **Clone the repository**:
    ```bash
    git clone https://github.com/ana147219/Cycle-Detection-and-Compensation-in-Directed-Graphs.git
    ```

2. **Compile the program**:
    ```bash
    gcc -o graph_program dz3p1.c
    ```

3. **Run the program**:
    ```bash
    ./graph_program
    ```

4. **Graph Operations**:
    - Option 1: Add a node to the graph
    - Option 2: Add an edge with weight
    - Option 6: Detect all cycles in the graph
    - Option 7: Detect cycles and calculate maximum compensation

## Future Improvements:
- **Graph Visualization**: Implement a visual representation of the graph and cycles to enhance user interaction.
- **Optimized Cycle Detection**: Improve the efficiency of the cycle detection algorithm for larger graphs.
- **User Interface**: Add a more user-friendly interface for easier interaction with graph operations.

## Conclusion:
The **Cycle Detection and Compensation in Directed Graphs** project is a powerful tool for studying graph theory concepts, specifically cycle detection and optimization within directed graphs. The program provides a solid foundation for future work in graph algorithms and optimization techniques.
