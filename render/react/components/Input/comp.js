import { getUid, setStyle } from '../config'

const bridge = globalThis.SJSJSBridge;
const NativeInput = bridge.NativeRender.NativeComponents.Input

function setImageProps(comp, newProps, oldProps) {
    const setter = {
        set style(styleSheet) {
            setStyle(comp, styleSheet);
        },
    }
    Object.assign(setter, newProps);
}
  
export class InputComp extends NativeInput {
    constructor (props) {
        const uid = getUid()
        super({ uid })
        this.uid = uid

        setTimeout(() => {
            console.log(typeof super.property('plainText'))
        })
    }
    setProps(newProps, oldProps) {
        setImageProps(this, newProps, oldProps);
    }
    insertBefore(child, beforeChild) {
    }
    static tagName = "input";
    appendInitialChild(child) {
    }
    appendChild(child) {
        
    }
    removeChild(child) {
        
    }
}