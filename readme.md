## Simulated Order Execution Protocol (SOE)
SOE is a simplified protocol that allows trading applications to interact with the simulated exchange over TCP/IP protocol. 

## Outbound Messages
Outbound messages are sent by the client to the exchange server.
#### New Order
Clients may place new limit orders to the book or consume existing liquidity by sending market orders to the exchange.

| Name            | Type         | Value          |
| :-------------  | :----------: | -----------:   |
|  `message-type` | `string`     | `E`            |
|  `order-type`   | `string`     | `LMT` or `MKT` |
|  `quantity`     | `int`        |                |
|  `price`        | `int`        |                |
|  `side`         | `string`     | `B`  or `S`    |

Note: Price is only applicable to limit orders.

Limit and market orders are identified by order-type as per below.

| Order Type      | Explanation  | 
| :-------------  | ----------:  | 
|  `LMT`          | `Limit Order`  |
|  `MKT`          | `Market Order`          | 

Buy or sell orders are identified by side as per below.

| Side            | Explanation  | 
| :-------------  | ----------:  | 
|  `S`            | `Sell`         |
|  `B`            | `Buy`          | 

#### Modify Order
Only limit orders may be modified. Order may be modified by submitting a new limit order with the same order id as the original one.

| Name            | Type         | Value          |
| :-------------  | :----------: | -----------:   |
|  `message-type` | `string`     | `E`            |
|  `order-type`   | `string`     | `LMT` or `MKT` |
|  `quantity`     | `int`        |                |
|  `price`        | `int`        |                |
|  `side`         | `string`     | `B`  or `S`    |
|  `order_id`     | `int`        |                |

The order id is received as an outbound message from the exchange in order accepted message.

#### Cancel Order
Only limit orders may be canceled. Order may only be canceled fully. Order is canceled by submitting an order cancel message that specifies an order id for the order that the client wants to cancel.

| Name            | Type         | Value          |
| :-------------  | :----------: | -----------:   |
|  `message-type` | `string`     | `X`            |
|  `order_id`     | `int`        |                |


## Inbound Messages
Inbound messages are received from the exchange.

#### Order Accepted
An Order Accepted message is sent as a response to an New Order request to acknowledge the client that the entered order was accepted by the exchange. The order id is the exchanges identifier for the order.

| Name            | Type         | Value          |
| :-------------  | :----------: | -----------:   |
|  `message-type` | `string`     | `A`            |
|  `order_id`     | `int`        |                |
|  `order-type`   | `string`     | `LMT` or `MKT` |
|  `quantity`     | `int`        |                |
|  `price`        | `int`        |                |
|  `side`         | `string`     | `B`  or `S`    |
|  `timestamp`    | `int`        |                |

#### Order Rejected

| Name            | Type         | Value          |
| :-------------  | :----------: | -----------:   |
|  `message-type` | `string`     | `R`            |
|  `order_id`     | `int`        |                |
|  `order-type`   | `string`     | `LMT` or `MKT` |
|  `quantity`     | `int`        |                |
|  `price`        | `int`        |                |
|  `side`         | `string`     | `B`  or `S`    |
|  `timestamp`    | `int`        |                |
|  `reason`       | `string`     | `P`  or `Q`    |

The reasons for a rejection are enumerated below.

| Side            | Explanation     | 
| :-------------  | ----------:     | 
|  `P`            | `Invalid price`   |
|  `Q`            | `Invalid quantity` | 

#### Order Executed
An Order Executed message indicates that an order sent by the client has been executed in part or fully. The match number is the order_id identifier for the trade.

| Name            | Type         | Value          |
| :-------------  | :----------: | -----------:   |
|  `message-type` | `string`     | `E`            |
|  `order_id`     | `int`        |                |
|  `order-type`   | `string`     | `LMT` or `MKT` |
|  `quantity`     | `int`        |                |
|  `price`        | `int`        |                |
|  `side`         | `string`     | `B`  or `S`    |
|  `timestamp`    | `int`        |                |
|  `liquidity`    | `string`     | `A`  or `R`    |

Side of the order execution is based on the original order that was executed.