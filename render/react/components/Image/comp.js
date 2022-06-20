import { getUid, setStyle } from '../config'

const bridge = globalThis.SJSJSBridge;
const NativeImage = bridge.NativeRender.NativeComponents.Image

function setImageProps(comp, newProps, oldProps) {
    const setter = {
        set style(styleSheet) {
            setStyle(comp, styleSheet);
        },
        set children(text) {
            text = Array.isArray(text) ? text.join('') : text;
            comp.setText(text);
        },
        set src(url) {
            if (url && url !== oldProps.url) {
                comp.setImage(url);
            }
        },
        set scaledContent (payload) {
            if (typeof payload === 'boolean' && payload !== oldProps.scaledContent) {
                comp.setScaleContent(payload)
            }
        }
    }
    Object.assign(setter, newProps);
}
  
export class ImageComp extends NativeImage {
    constructor (props) {
        const uid = getUid()
        super({ uid })
        this.uid = uid
    }
    setProps(newProps, oldProps) {
        setImageProps(this, newProps, oldProps);
    }
    insertBefore(child, beforeChild) {
    }
    static tagName = "image";
    appendInitialChild(child) {
    }
    appendChild(child) {
        
    }
    removeChild(child) {
        
    }
}