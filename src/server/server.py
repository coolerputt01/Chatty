import asyncio
from websockets.asyncio.server import serve


consumers = set()

async def ws_handler(client):
    consumers.add(client)
    try:
        async for message in client:
            print(f"Received message from client:{message}")
            for consumer in consumers:
                if consumer != client:
                    await consumer.send(message);
    except websockets.exceptions.ConnectedClosed:
        raise f"Websocket connection closed."
    finally:
        consumers.remove(client)

async def main():
    async with serve(ws_handler,"localhost",5000) as server:
        print("Server running at ws://localhost:5000...\n")
        await server.serve_forever()


if __name__ == '__main__':
    asyncio.run(main())