from flask import Flask, request, jsonify, render_template
import amdisa

app = Flask(__name__)

decoder = amdisa.decoder()
try:
    decoder.init("/mnt/c/Users/kabylkas/OneDrive/Desktop/isa_spec_manager/xmls/mi100.xml")
except RuntimeError as e:
    print(e)
    exit(1)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/send_message', methods=['POST'])
def send_message():
    # Get data.
    data = request.json
    inst = int(data.get('message'), 16)

    # Decode instruction.
    inst_info = decoder.decode(inst)

    # Process the message (for example, reverse the text)
    response_message = "{}: {}".format(inst_info.name, inst_info.description)
    return jsonify({'response': response_message})

if __name__ == '__main__':
    app.run(debug=True)
