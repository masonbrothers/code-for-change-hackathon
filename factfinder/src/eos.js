import { Api, JsonRpc, RpcError } from 'eosjs';
import { JsSignatureProvider } from 'eosjs/dist/eosjs-jssig';  

export default class {
    static post = async (key, name, message) => {
        const signatureProvider = new JsSignatureProvider([key]);
        const rpc = new JsonRpc('http://127.0.0.1:8888', { fetch });
        const api = new Api({ rpc, signatureProvider, textDecoder: new TextDecoder(), textEncoder: new TextEncoder() });
        const result = await api.transact({
            actions: [{
            account: 'factfinder',
            name: 'post',
            authorization: [{
                actor: name,
                permission: 'active',
            }],
            data: {
                poster: name,
                message: message
            },
            }]
        }, {
            blocksBehind: 3,
            expireSeconds: 30,
        });
        console.dir(result);
    }

    static castvote = async (key, name, message_id, amount, is_true) => {
        const signatureProvider = new JsSignatureProvider([key]);
        const rpc = new JsonRpc('http://127.0.0.1:8888', { fetch });
        const api = new Api({ rpc, signatureProvider, textDecoder: new TextDecoder(), textEncoder: new TextEncoder() });
        const result = await api.transact({
            actions: [{
            account: 'factfinder',
            name: 'castvote',
            authorization: [{
                actor: name,
                permission: 'active',
            }],
            data: {
                voter: name,
                message_id: message_id,
                amount: amount,
                is_true: is_true
            },
            }]
        }, {
            blocksBehind: 3,
            expireSeconds: 30,
        });
        console.dir(result);

    }
}
