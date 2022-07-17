
import { registEvent, unRegistEvent } from '../core/event'

const components = new Map;

let id = 1;

export const getUid = () => {
    return String(id++);
}

export const getComponentByTagName = (tagName) => {
    const config = components.get(tagName);
    if (!config) {
      throw `Unknown component ${tagName}`;
    }
    return config;
};
  
export function registerComponent(
    config
) {
    if (components.has(config.tagName)) {
        throw `A component with tagName: ${config.tagName} already exists. This base component will be ignored`;
    }
    components.set(config.tagName, config);
    return config.tagName;
}

export function registerComponents(
    configs
) {
    configs.forEach(config => {
        if (components.has(config.tagName)) {
            throw `A component with tagName: ${config.tagName} already exists. This base component will be ignored`;
        }
        components.set(config.tagName, config);
    })
}

export function setStyle (comp, obj) {
    const styleObj = Array.isArray(obj) ? Object.assign({}, ...obj.filter(Boolean)) : obj
    let str = StyleSheet.transform(styleObj)
    str = `#${comp.uid} {${str}}`
    comp.setStyle(str)
}

export function handleOnClick (comp, fn) {
    if (fn) {
        registEvent(comp.uid, 'click', fn)
        comp.addEventListener('click')
    } else {
        unRegistEvent(comp.uid, 'click')
        comp.removeEventListener('click')
    }
}

export function handleOnTextChange (comp, fn) {
    if (typeof fn !== 'function') return;
    try {
        if (fn) {
            registEvent(comp.uid, 'textChange', fn)
            comp.addEventListener('textChange')
        } else {
            unRegistEvent(comp.uid, 'textChange')
            comp.removeEventListener('textChange')
        }
    } catch (e) {
        console.log(e)
    }
}

export function handleOnFocus (comp, fn) {
    if (typeof fn !== 'function') return;
    try {
        if (fn) {
            registEvent(comp.uid, 'focus', fn)
            comp.addEventListener('focus')
        } else {
            unRegistEvent(comp.uid, 'focus')
            comp.removeEventListener('focus')
        }
    } catch (e) {
        console.log(e)
    }
}

export function handleOnBlur (comp, fn) {
    if (typeof fn !== 'function') return;
    try {
        if (fn) {
            registEvent(comp.uid, 'blur', fn)
            comp.addEventListener('blur')
        } else {
            unRegistEvent(comp.uid, 'blur')
            comp.removeEventListener('blur')
        }
    } catch (e) {
        console.log(e)
    }
}