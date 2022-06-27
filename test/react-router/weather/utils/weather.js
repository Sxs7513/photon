export const getCurrentWeather = () => {
    return new Promise((resolve, reject) => {
        // resolve({"coord":{"lon":18.0649,"lat":59.3326},"weather":[{"id":804,"main":"Clouds","description":"overcast clouds","icon":"04d"}],"base":"stations","main":{"temp":13.83,"feels_like":13.23,"temp_min":12.81,"temp_max":15.48,"pressure":1013,"humidity":75},"visibility":10000,"wind":{"speed":5.14,"deg":250},"clouds":{"all":91},"dt":1655009205,"sys":{"type":1,"id":1788,"country":"SE","sunrise":1654997560,"sunset":1655064157},"timezone":7200,"id":2673730,"name":"Stockholm","cod":200})

        let apiKey = "15e768797b4bf44b49979df29e6da67a";
        let city = "Stockholm";
        let url = `http://api.openweathermap.org/data/2.5/weather?q=${city}&appid=${apiKey}&units=metric`;
        
        const xhr = new XMLHttpRequest();
        xhr.onloadend = (response) => {
            console.log(response.data)
            resolve(JSON.parse(response.data))
        };
        xhr.open('GET', url);
        xhr.send();
    })
};