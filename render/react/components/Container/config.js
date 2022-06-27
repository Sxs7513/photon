import { Container } from './comp'

export default class ContainerConfig {
    tagName = 'container';
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
        const instance = new Container();
        instance.setProps(newProps, {});
        return instance;
    }
    commitMount(
        instance,
        props,
        internalInstanceHandle
    ) {
        props.minSize && instance.setMinimumSize(props.minSize.width, props.minSize.height);
        props.maxSize && instance.setMaximumSize(props.maxSize.width, props.maxSize.height);
        instance.show()
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
