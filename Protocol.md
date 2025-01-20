# Protocol Design

## Message Structure
Every message has:
1. Components.
2. Delimiters.

### 1. Message Components
Each message contains four mandatory components, each serving a distinct and essential purpose.
Components are separated by the delimiter `|`, and each component contains a key-value pair separated by the delimiter `:` for clarity and structure.

#### 1.1. ID:
A unique identifier used to:
- Distinctly identify a message.
- Match a message with its corresponding response.

#### 1.2. Type: 
- Identifies the type of the message.
- Helps the receiver (server or agent) understand its overall purpose.
- The Message `TYPE` can be one of the following:
    - `REGISTER`: A request for the agent to register itself upon connecting.
    - `COMMAND`: A directive from the server to the agent to perform specific operations.
    - `HEARTBEAT`:
        - A status report message from the agent to the server.
        - A query message from the server to the agent requesting further status information.
    - `RESPONSE`: A reply to a previous message, sent by either the server or agent.

#### 1.3. Action:
- Specifies the operation to be performed within the `TYPE`.
- Provides granularity to the message's intent.
- Actions per `TYPE` are as follows:
    - `REGISTER`: 
        - `REQUEST`: Sent by the server to instruct the agent to register itself.
    - `COMMAND`: 
        - `EXEC`: Execute a specified shell command.
        - `UPLOAD`: Upload a file from the agent to the server.
        - `DOWNLOAD`: Download a file from the server to the agent.
        - `SLEEP`: Instruct the agent to pause its operation for a specified duration.
        - `TERMINATE`: Instruct the agent to terminate its connection and shut down.
    - `HEARTBEAT`:
        - `STATUS`: The agent sends its status.
        - `QUERY`: The server requests the agent for specific status details.
    - `RESPONSE`:
        - `RESULT`: The agent or server sends the result of a previously requested operation.
        - `ERROR`: Indicates an error encountered during a requested operation.

#### 1.4. Data:
Holds the payload of the message, which varies depending on the `TYPE` and `ACTION`.
The `DATA` component:
- Contains specific values required for the operation.
    - Example with data: `ID:ABC123|TYPE:COMMAND|ACTION:EXEC|DATA:whoami`
- Is set to `-` when no data is needed for the message.
    - Example without data: `ID:XYZ456|TYPE:COMMAND|ACTION:TERMINATE|DATA:-`

### 2. Message Delimiters
Messages may contain 3 different delimiters, each serving a specific purpose:
- `:` separates the key from its value within a component.
- `|` separates individual components.
- `,` separates multiple values within the `DATA` component.


