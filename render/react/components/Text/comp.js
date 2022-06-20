import { getUid, setStyle } from '../config'

const bridge = globalThis.SJSJSBridge;
const NativeText = bridge.NativeRender.NativeComponents.Text

function setTextProps(comp, newProps, oldProps) {
    const setter = {
        set style(styleSheet) {
            setStyle(comp, styleSheet);
        },
        set children(text) {
            text = Array.isArray(text) ? text.join('') : text;
            comp.setText(text);
        },
    }
    Object.assign(setter, newProps);
}
  
export class TextComp extends NativeText {
    constructor (props) {
        const uid = getUid()
        super({ uid })
        this.uid = uid
    }
    setProps(newProps, oldProps) {
        setTextProps(this, newProps, oldProps);
    }
    insertBefore(child, beforeChild) {
    }
    static tagName = "text";
    appendInitialChild(child) {
    }
    appendChild(child) {
        
    }
    removeChild(child) {
        
    }
}