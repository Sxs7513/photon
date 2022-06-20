const bridge = globalThis.SJSJSBridge;
// async function start () {
//     try {
//         const res2 = await bridge.net.getAddrInfo('google.cn', 'http', { socktype: bridge.SOCK_STREAM, protocol: bridge.IPPROTO_TCP });
//         bridge.console.log(res2[0].ip)
//     } catch (e) {
//         bridge.console.log(e)
//     }
// }
// start()
console.log(`js code run`)
globalThis.a = (arg) => {
    console.log(`native pass value is ${arg}`)
}
const view = new bridge.NativeRender.NativeComponents.view
console.log(typeof view.show)

console.log(typeof React)