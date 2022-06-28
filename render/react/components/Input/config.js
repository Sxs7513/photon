import { InputComp } from './comp'

export default class InputConfig {
    tagName = 'input';
    native = null;
    shouldSetTextContent() {
        return false;
    }
    createInstance(
        newProps,
        rootInstance,
        context,
        workInProgress
    ) {
        const instance = new InputComp();
        instance.setProps(newProps, {});
        return instance;
    }
    commitMount(
        instance,
        newProps,
        internalInstanceHandle
    ) {
    }
    commitUpdate(
        instance,
        updatePayload,
        oldProps,
        newProps,
        finishedWork
    ) {
        instance.setProps(newProps, oldProps);
    }
    setProps(newProps, oldProps) {
    }
    insertBefore(child, beforeChild) {

    }
    appendInitialChild(child) {
    }
    appendChild(child) {
        
    }
    removeChild(child) {
    }
}
