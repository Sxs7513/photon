import { getUid, setStyle, handleOnTextChange,handleOnFocus, handleOnBlur } from '../config'

const bridge = globalThis.SJSJSBridge;
const NativeInput = bridge.NativeRender.NativeComponents.Input

function setInputProps(comp, newProps, oldProps) {
    const setter = {
        set style(styleSheet) {
            setStyle(comp, styleSheet);
        },
        set onChange (fn) {
            handleOnTextChange(comp, fn);
        },
        set onFocus (fn) {
            handleOnFocus(comp, fn);
        },
        set onBlur (fn) {
            handleOnBlur(comp, fn);
        }
    }
    Object.assign(setter, newProps);
}
  
export class InputComp extends NativeInput {
    constructor (props) {
        const uid = getUid()
        super({ uid })
        this.uid = uid
    }
    setProps(newProps, oldProps) {
        setInputProps(this, newProps, oldProps);
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

    get text () {
        return this.property("text")?.toString() || "";
    }
}