# Lesson 48: Observer and Event System

The Observer pattern (also called Publish/Subscribe) decouples event producers
from event consumers. The emitter fires events without knowing who is
listening; observers register callbacks and react when notified.

## Exercises

| #  | File     | Topic                  | Key Idea |
|----|----------|------------------------|----------|
| 01 | ex01.h   | Simple Event Emitter   | on() + emit() basics |
| 02 | ex02.h   | Subscription ID        | Unsubscribe with off(id) |
| 03 | ex03.h   | Multi-event Dispatcher | Named events with separate listener lists |
| 04 | ex04.h   | Event with Payload     | Template emitter carrying typed data |
| 05 | ex05.h   | Auto-unsubscribe       | RAII Subscription handle |
| 06 | ex06.h   | Weak Observer          | Non-owning weak_ptr references |
| 07 | ex07.h   | Event Filtering        | Predicate-gated listeners |
| 08 | ex08.h   | Ordered Dispatch       | Priority-based notification order |
