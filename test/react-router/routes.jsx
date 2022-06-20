import Calculator from "./calculator";
import Weather from "./weather";
import Home from "./home";
import { Route, Routes } from 'react-router'

export default function AppRoutes() {
  return (
    <Routes>
      <Route exact path="/calculator" element={<Calculator />} />
      <Route path="/weather" element={<Weather />} />
      <Route path="/" element={<Home />} />
    </Routes>
  );
}