import * as react from 'react'
import ViewConfig from "./components/View/config";
import TextConfig from "./components/Text/config";
import ButtonConfig from "./components/Button/config";
import ContainerConfig from "./components/Container/config";
import ImageConfig from './components/Image/config';
import ScrollViewConfig from './components/ScrollView/config';
import InputConfig from './components/Input/config';
import { registerComponent } from "./components/config";
import { Renderer } from "./core/renderer";
import StyleSheet from './core/style'

export const View = registerComponent(new ViewConfig());
export const Button = registerComponent(new ButtonConfig());
export const Container = registerComponent(new ContainerConfig());
export const Text = registerComponent(new TextConfig());
export const Image = registerComponent(new ImageConfig());
export const ScrollView = registerComponent(new ScrollViewConfig());
export const Input = registerComponent(new InputConfig());

globalThis.Renderer = Renderer;

globalThis.React = react;

globalThis.StyleSheet = StyleSheet;