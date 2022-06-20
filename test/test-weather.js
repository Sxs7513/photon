// test/weather/utils/weather.js
var getCurrentWeather = () => {
  return new Promise((resolve, reject) => {
    let apiKey = "15e768797b4bf44b49979df29e6da67a";
    let city = "Stockholm";
    let url = `http://api.openweathermap.org/data/2.5/weather?q=${city}&appid=${apiKey}&units=metric`;
    const xhr = new XMLHttpRequest();
    xhr.onloadend = (response) => {
      console.log(response.data);
      resolve(JSON.parse(response.data));
    };
    xhr.open("GET", url);
    xhr.send();
  });
};

// test/weather/components/WeatherIcon.jsx
import path from "path";
var rootDir = path.resolve(import.meta.dirname, "./");
var assetUrl = path.resolve(rootDir, "assets/icons");
var WeatherIcon = (props) => {
  const iconId = props.icon || "na";
  const imageUrl = `${path.resolve(assetUrl, `${iconId}.png`)}`;
  return /* @__PURE__ */ React.createElement("image", {
    style: props.style || "",
    src: imageUrl,
    scaledContent: true
  });
};

// test/weather/components/TemperatureBox.jsx
var TemperatureBox = (props) => {
  return /* @__PURE__ */ React.createElement("view", {
    style: style.temperatureBoxStyle
  }, /* @__PURE__ */ React.createElement("text", {
    style: style.currentTempStyle
  }, `${props.now} <sup>o</sup>C`), /* @__PURE__ */ React.createElement("view", {
    style: style.smallBox
  }, /* @__PURE__ */ React.createElement("text", {
    style: style.smallInfo
  }, `${props.min} <sup>o</sup>C / ${props.max} <sup>o</sup>C`)));
};
var style = StyleSheet.create({
  currentTempStyle: {
    "font-size": "20px",
    "text-align": "center",
    "color": "white"
  },
  temperatureBoxStyle: {
    "border-right": "1px solid white",
    "flex": 1,
    "flex-shrink": 0,
    "flex-grow": 0,
    "align-items": "center",
    "justify-content": "center",
    "flex-direction": "column"
  },
  smallBox: {
    "flex-direction": "row",
    "align-items": "center",
    "justify-content": "center"
  },
  smallInfo: {
    "width": "150px",
    "color": "white",
    "text-align": "center"
  }
});

// test/weather/components/Summary.jsx
var Summary = (props) => {
  return /* @__PURE__ */ React.createElement("view", {
    style: style2.containerStyle
  }, /* @__PURE__ */ React.createElement("text", {
    style: style2.textStyle
  }, `<b>${props.title}</b>: <i>${props.description}</i>.`));
};
var style2 = StyleSheet.create({
  containerStyle: {
    "align-items": "center",
    "justify-content": "center",
    "height": "50px",
    "flex-shrink": 0,
    "flex-grow": 0
  },
  textStyle: {
    "text-align": "center",
    "color": "white",
    "height": "30px"
  }
});

// test/weather/utils/helpers.js
var dateFormatter = (date) => {
  const monthNames = [
    "Jan",
    "Feb",
    "Mar",
    "Apr",
    "May",
    "Jun",
    "Jul",
    "Aug",
    "Sep",
    "Oct",
    "Nov",
    "Dec"
  ];
  const day = date.getDate();
  const monthIndex = date.getMonth();
  const year = date.getFullYear();
  return `${day} ${monthNames[monthIndex]} ${year}`;
};

// test/weather/components/PlaceDate.jsx
var PlaceDate = (props) => {
  return /* @__PURE__ */ React.createElement("view", {
    style: style3.containerStyle
  }, /* @__PURE__ */ React.createElement("text", {
    style: style3.placeStyle
  }, props.place), /* @__PURE__ */ React.createElement("text", {
    style: style3.dateStyle
  }, dateFormatter(props.date)));
};
var style3 = StyleSheet.create({
  placeStyle: {
    "font-size": "20px",
    "color": "white"
  },
  dateStyle: {
    "font-size": "12px",
    "color": "white"
  },
  containerStyle: {
    "display": "flex",
    "flex": 1,
    "flex-shrink": 0,
    "flex-direction": "column",
    "justify-content": "center",
    "align-items": "center"
  }
});

// test/weather/index.jsx
import path2 from "path";
var { useState, useEffect, useCallback } = React;
var defaultState = {
  weather: [],
  main: {
    temp: 0,
    temp_min: 0,
    temp_max: 0
  },
  name: "NA"
};
var App = () => {
  const [weather, setWeather] = useState(defaultState);
  const getWeather = useCallback(async () => {
    try {
      const data = await getCurrentWeather();
      setWeather(data);
    } catch (err) {
      console.log(err);
    }
  }, []);
  useEffect(() => {
    getWeather();
  }, []);
  const summary = weather.weather[0] || {};
  return /* @__PURE__ */ React.createElement("container", {
    maxSize: { width: 500, height: 700 },
    minSize: { width: 400, height: 600 }
  }, /* @__PURE__ */ React.createElement("view", {
    style: style4.wrapper
  }, /* @__PURE__ */ React.createElement("image", {
    style: style4.backgroundImage,
    src: path2.resolve(import.meta.dirname, "./assets/images/sky.jpg"),
    scaledContent: true
  }), /* @__PURE__ */ React.createElement("view", {
    style: style4.iconWrapper
  }, /* @__PURE__ */ React.createElement(WeatherIcon, {
    icon: summary.icon,
    style: style4.icon
  })), /* @__PURE__ */ React.createElement("view", {
    style: style4.details
  }, /* @__PURE__ */ React.createElement(Summary, {
    title: summary.main,
    description: summary.description
  }), /* @__PURE__ */ React.createElement("view", {
    style: style4.midBox
  }, /* @__PURE__ */ React.createElement(TemperatureBox, {
    now: weather.main.temp,
    max: weather.main.temp_max,
    min: weather.main.temp_min
  }), /* @__PURE__ */ React.createElement(PlaceDate, {
    place: weather.name,
    date: new Date()
  })), /* @__PURE__ */ React.createElement("view", {
    style: style4.buttonBox
  }, /* @__PURE__ */ React.createElement("button", {
    text: "Refresh",
    style: style4.button1
  }), /* @__PURE__ */ React.createElement("button", {
    text: "Close",
    style: style4.button2
  })))));
};
var style4 = StyleSheet.create({
  wrapper: {
    "width": "100%",
    "height": "100%",
    "position": "relative",
    "display": "flex",
    "flex-direction": "column",
    "align-items": "center"
  },
  iconWrapper: {
    "height": "50%",
    "justify-content": "flex-end"
  },
  icon: {
    "width": "200px",
    "height": "200px"
  },
  backgroundImage: {
    "width": "100%",
    "height": "100%",
    "position": "absolute",
    "left": 0,
    "right": 0
  },
  midBox: {
    "flex-direction": "row",
    "width": "100%",
    "flex-shrink": 0,
    "flex-grow": 0
  },
  buttonBox: {
    "height": "30px",
    "margin-top": "20px",
    "flex-direction": "row",
    "justify-content": "center",
    "flex-shrink": 0,
    "flex-grow": 0
  },
  button1: {
    "margin-right": "10px",
    "width": "80px"
  },
  button2: {
    "width": "80px"
  },
  details: {
    "width": "80%",
    "height": "150px",
    "justify-content": "flex-start",
    "flex-direction": "column",
    "border-radius": "5px",
    "background-color": "qlineargradient( x1:0 y1:0, x2:0 y2:1, stop:0 rgba(32,65,106,0.6), stop:1 rgba(8,8,8,0.6))"
  }
});
Renderer.render(/* @__PURE__ */ React.createElement(App, null));
