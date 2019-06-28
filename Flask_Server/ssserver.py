from flask import Flask, request
from flask_session import Session
from flask_socketio import SocketIO, emit

app=Flask(__name__)

app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)

@app.route("/")
def index() :
    return "Hi Everyone, My name is Karan Rathore "

@app.route("/hello", methods=["GET","POST"])
def hello():
    if request.method == "POST":
        name = "you send some thing wrong"
        name = request.form.get("name")
        if name is None :
            name = "wrong argument passed"
        return "Hello, you send post request with " + name
    else :
        return "Hello, its GET request"

@app.route("/find")
def search():
    data = request.args.get("name")
    return "this is what you send stupid " +data



if __name__== "__main__":
    app.run(host="192.168.0.101", port="5004")

