// const apiLink=`https://api.openweathermap.org/data/2.5/weather?q='${city}'&units=metric&appid=e2f377dc361806f55f4a9f3dd021bd6a`;

const searchInput = document.getElementById('input1')
const button = document.getElementById('btn1')

button.addEventListener('click', () => {
    // console.log(searchInput.value);
    weatherReport(searchInput.value);
    
});

function weatherReport(city) {
    fetch(`https://api.openweathermap.org/data/2.5/weather?q=${city}&units=metric&appid=e2f377dc361806f55f4a9f3dd021bd6a`)
        .then(Response => Response.json())
        .then(showWeatherReport)
.catch(err => console.log("Error in Code ,to see the error please comment out 'catch' method"));
};

function showWeatherReport(weather) {
    console.log(weather);
    let city = document.getElementById("weather_city_name");
    city.innerHTML = `${weather.name}`;

    let temperature = document.getElementById("weather_temp");
    temperature.innerHTML = `${weather.main.temp}°C`;

    let weatherType=document.getElementById('clouds');
    weatherConditions=`${weather.weather[0].main}`;
    weatherType.innerHTML=weatherConditions;

    let day =document.getElementById("weather_day");
    const currentDate = new Date();
    day.innerHTML=otherStuff(currentDate);

    // to change icon according to weather conditions
    let weather_icon=document.getElementById('weather_icon');

    if (weatherConditions=="Clouds") {
        weather_icon.innerHTML=`<i class="fas fa-cloud"></i>`;
    }else if(weatherConditions=='Sunny') {
        weather_icon.innerHTML=`<i class="fas fa-sun"></i>`;
    }else if(weatherConditions=='Rain') {
        weather_icon.innerHTML='<i class="fas fa-cloud-showers-heavy"></i>';
    }else if(weatherConditions=='Haze') {
        weather_icon.innerHTML='<i class="fas fa-smog"></i>';
    }else{
        weather_icon.innerHTML=`<i class="fas fa-cloud-sun"></i>`;
    };

};

function otherStuff(dateDayMonthYear) {
    const months = ["Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"];

    const days = ['Sunday', 'Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday'];

    let day=days[dateDayMonthYear.getDay()];
    let date=dateDayMonthYear.getDate();
    let month=months[dateDayMonthYear.getMonth()];
    let year=dateDayMonthYear.getFullYear();

    return `${day} , ${date}/${month}/${year}`
    
}



