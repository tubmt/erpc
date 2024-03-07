# eRPC Java Infrastructure

This folder contains the Java implementation of the eRPC infrastructure.

## Contents

- `/src/main/java/io/github/embeddedrpc/erpc` - Java package containing eRPC infrastructure.
- `pom.xml` - Maven config file.
- `checkstyle.xml` - Check style config file.

## Prerequisites

- [Java 21 SDK](https://jdk.java.net/21/)
- [Maven 3.9.5](https://maven.apache.org/download.cgi)

To check that all the prerequisites are correctly installed, run `mvn -v`. You should get something like this:

```
Apache Maven 3.9.5 (***)
Maven home: c:\Program Files\maven\apache-maven-3.9.5
Java version: 21, vendor: Oracle Corporation, runtime: c:\Program Files\Java\jdk-21
Default locale: en_US, platform encoding: UTF-8
OS name: "***", version: "***", arch: "***", family: "***"
```

- If `mvn -v` fails, check that you have added maven to the `PATH` variable.
- If you do not see the correct Java version, check that you have set the `JAVA_HOME` and `PATH` variables correctly.


## Installation

1. Run `mvn install` to download all dependencies and install eRPC to local maven repository.
2. Move to `erpc_java` and run `mvn install` to download all dependencies and build eRPC Java library.
3. Output `erpc/erpc_java/target/erpc-0.1.0.jar`
4. Move to `erpcgen` and run `make -f Makefile` to build `erpcgen tool`
5. Output `erpc/Release/Darwin/erpcgen/erpcgen`
5. Uses `erpcgen tool` to generate the shim code. Run `erpcgen -g java erpc_my_test.erpc`

## Usage

### eRPC
#### erpc_my_test.erpc
````eRPC
/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

program erpc_my_test

const int32 PORT = 40;
const string HOST = "localhost";

interface MyTest {
    foo(in int32 a, in int32 b) -> int32
}
````

### Client

```Java
import  io.github.embeddedrpc.erpc.auxiliary.Reference;
import  io.github.embeddedrpc.erpc.client.ClientManager;
import  io.github.embeddedrpc.erpc.codec.BasicCodecFactory;
import  io.github.embeddedrpc.erpc.transport.TCPTransport;
import  io.github.embeddedrpc.erpc.transport.Transport;

import com.example.app.client.MyTestClient;

public class Main {
    public static void main(String[] args) {
        Transport transport = new TCPTransport("localhost", 40);

        ClientManager clientManager = new ClientManager(transport, new BasicCodecFactory());
        MyTestClient client = new MyTestClient(clientManager);

        Reference<String> out;
        int result;
        
        result = client.foo(42, 8);
        client.boo("John", out);
    }
}
```

### Server
#### Main.java
```Java
import  io.github.embeddedrpc.erpc.server.Server;
import  io.github.embeddedrpc.erpc.server.SimpleServer;
import  io.github.embeddedrpc.erpc.codec.BasicCodecFactory;
import  io.github.embeddedrpc.erpc.transport.TCPTransport;
import  io.github.embeddedrpc.erpc.transport.Transport;

import com.example.app.MyTestService;

public class Main {
    public static void main(String[] args) {
        Transport transport = new TCPTransport(40);

        Server server = new SimpleServer(transport, new BasicCodecFactory());

        server.addService(new MyTestService());

        server.run();
    }
}
```
#### MyTestService.java

```Java
import  io.github.embeddedrpc.erpc.auxiliary.Reference;
import com.example.app.server.AbstractMyTestService;

public class MyTestService extends AbstractMyTestService {
    @Override
    public int foo(int a, int b) {
        return a + b;
    }
}
```