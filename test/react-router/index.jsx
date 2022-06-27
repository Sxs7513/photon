
import '../../render/react'

import AppRoutes from "./routes";
import { MemoryRouter } from "react-router";

const minSize = { width: 500, height: 520 };

function App () {
  return  (
    <MemoryRouter>
      <container minSize={minSize}>
        <view style={style.wrapper}>
          <AppRoutes />
        </view>
      </container>
    </MemoryRouter>
  );
}

const style = StyleSheet.create({
  wrapper: {
    "flex": 1,
    "height": '100%',
    "border": "1px solid blue"
  }
})

console.log(22222222222)

Renderer.render(<App />);