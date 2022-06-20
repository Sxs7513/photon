import * as react from 'react'
import ViewConfig from "./components/View/config";
import TextConfig from "./components/Text/config";
import ButtonConfig from "./components/Button/config";
import ContainerConfig from "./components/Container/config";
import ImageConfig from './components/Image/config';
import { registerComponent } from "./components/config";
import { Renderer } from "./core/renderer";
import StyleSheet from './core/style'

export const View = registerComponent(new ViewConfig());
export const Button = registerComponent(new ButtonConfig());
export const Container = registerComponent(new ContainerConfig());
export const Text = registerComponent(new TextConfig());
export const Image = registerComponent(new ImageConfig());

globalThis.Renderer = Renderer

globalThis.React = react

globalThis.StyleSheet = StyleSheet

globalThis.xh = globalThis.SJSJSBridge