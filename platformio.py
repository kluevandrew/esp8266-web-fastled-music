import json
import os.path
Import("env")

if os.path.isfile('device.json'):
    with open('device.json') as json_file:
        data = json.load(json_file)
        if env['UPLOAD_PROTOCOL'] == 'espota':
            env.Replace(UPLOAD_PORT=data['ip'])
            if data['pass']:
                env.Replace(UPLOAD_FLAGS="$UPLOAD_FLAGS --auth " + data['pass'])
        else:
            env.Replace(UPLOAD_PORT=data['usb'])