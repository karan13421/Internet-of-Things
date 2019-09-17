from flask import Flask, request
from flask_session import Session
from flask_socketio import SocketIO, emit
import eventlet
import socketio

app=Flask(__name__)

app.config['SECRET_KEY'] = 'secret!'
sio = socketio.Server()

@sio.on("messages")
def message(message):
    message="oooooooooooooooooooooooooooooo"
    print("Connected")
    emit("message", message)

@sio.on('connect')
def test_connect(arg1, arg2):
    print('Client connected')
    sio.emit('message', {'data': 'Connected'})
 


#@app.route("/messages")
#def messsage():
#    message = "this"
#    print(message)
#    emit("messages", message, broadcast=True)
#    return "ok"




if __name__== "__main__":
    app = socketio.Middleware(sio, app)
    eventlet.wsgi.server(eventlet.listen(('192.168.1.104', 5000)), app)    

