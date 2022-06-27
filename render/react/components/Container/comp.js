import { getUid, setStyle } from '../config'

const bridge = globalThis.SJSJSBridge;
const NativeComp = bridge.NativeRender.NativeComponents.Container

function setContainerProps(comp, newProps, oldProps) {
    const setter = {
        set style(styleSheet) {
            setStyle(comp, styleSheet);
        },
        set title (title) {
            if (oldProps.title != title) {
                comp.setTitle(title);
            }
        }
    }
    Object.assign(setter, newProps);
}

export class Container extends NativeComp {
    constructor (props) {
        const uid = getUid()
        super({ uid })
        this.uid = uid
    }
    setProps(newProps, oldProps) {
        setContainerProps(this, newProps, oldProps);
    }
    insertBefore(child, beforeChild) {
    }
    static tagName = "container";
    appendInitialChild(child) {
        this.appendChild(child);
    }
    appendChild(child) {
        super.appendChild(child);
        child.setFlexNodeSizeControlled(true);
    }
    removeChild(child) {

    }
}