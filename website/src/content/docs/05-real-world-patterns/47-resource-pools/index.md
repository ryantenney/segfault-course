---
title: "Lesson 47: Resource Pools"
---

Resource pools manage reusable objects that are expensive to create (database
connections, thread contexts, GPU buffers). Instead of constructing and
destroying them on every use, the pool keeps a reserve of idle objects ready to
hand out.

## Exercises

| #  | File     | Topic                  | Key Idea |
|----|----------|------------------------|----------|
| 01 | ex01.h   | Basic Object Pool      | acquire / release with a simple vector |
| 02 | ex02.h   | RAII Pool Handle       | Auto-return on scope exit |
| 03 | ex03.h   | Pool with Factory      | On-demand creation up to a limit |
| 04 | ex04.h   | Thread-safe Pool       | Mutex + condition variable |
| 05 | ex05.h   | Pool with Health Check | Validate-before-use pattern |
| 06 | ex06.h   | Pool Statistics        | Track active, idle, and total counts |
| 07 | ex07.h   | Pool with Timeout      | Timed wait with std::optional result |
