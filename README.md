<div align="center" style="font-family: Arial, sans-serif; line-height: 1.6; color: #333;">
  <h1 style="font-size: 3rem; font-weight: bold; color: #0078d7; text-transform: uppercase;">SOHYPON</h1>
  <h2 style="color: black; font-weight: 700; text-transform: uppercase; text-shadow: 2px 2px 3px gray, 0 0 1em white; margin-bottom: 2rem;">
    This is a current work in progress project.
  </h2>

 <div>
   Sensors 
  <br />(pH, Air Quality, Distance)
  <br />Collect environmental data.

↓

Arduino R4 WiFi 
<br />(Data Processing)
<br />Processes and sends sensor data to the backend.

↓

NestJS 
<br />(Backend Framework)
<br />Manages server-side logic, processes data, and interacts with the database.

↓

ORM
<br />(Object Relational Mapper)
<br />Handles communication between the backend (NestJS) and the database.

↓

Database
<br />(PostgreSQL)
<br />Stores data for analysis, monitoring, and retrieval.

↑
ORM
<br />(Object Relational Mapper)
<br />Handles communication between the backend (NestJS) and the database.
↑

NestJS 
<br />(Backend Framework)
<br />Manages server-side logic, processes data, and interacts with the database.

↑

Frontend 
<br />(React)
<br />Displays data to users through a responsive interface.

↓

Raspberry Pi 5 
<br />(App and FrontEnd Host)
<br />Hosts the user interface and supports backend processing.
 </div>
<hr />
  <h3 style="font-size: 1.8rem; font-weight: bold; margin-bottom: 1rem;">Product List</h3>

  <div style="max-width: 800px; margin: 0 auto;">
    <table style="width: 100%; border-collapse: collapse; border: 1px solid #ddd;">
      <tr>
        <th style="background-color: #f4f4f4; padding: 10px; border: 1px solid #ddd; font-size: 1.2rem;">Hardware List</th>
        <th style="background-color: #f4f4f4; padding: 10px; border: 1px solid #ddd; font-size: 1.2rem;">Software List</th>
      </tr>
      <tr>
        <td style="padding: 10px; border: 1px solid #ddd; vertical-align: top;">
          <ul style="list-style: none; padding: 0; margin: 0;">
            <li>
              <h4 style="text-decoration: underline;">Electronics</h4>
              <ul>
                <li>Raspberry Pi 5</li>
                <li>Arduino Uno R4 Wifi</li>
              </ul>
            </li>
            <li>
              <h4 style="text-decoration: underline;">Sensors</h4>
              <ul>
                <!-- <li>3 x Voltage Dividers</li> -->
                <!-- <li>Air Quality Sensor</li> -->
                <li>Adafruit BME680</li>
                <li>pH Sensor</li>
                <li>Ultrasonic Distance Sensor (HC-SR04)</li>
              </ul>
            </li>
            <li>
              <h4 style="text-decoration: underline;">Components</h4>
              <ul>
                <li>300W Solar Panel</li>
                <li>Charge Controller</li>
                <!-- <li>2000W Inverter</li> -->
                <li>2 x 12V Lead Acid Batteries | 200AH (each)</li>
                <li>12V Water Pump</li>
              </ul>
            </li>
          </ul>
        </td>
        <td style="padding: 10px; border: 1px solid #ddd; vertical-align: top;">
          <ul style="list-style: none; padding: 0; margin: 0;">
            <li>
              <h4 style="text-decoration: underline;">IDE's</h4>
              <ul>
                <li>Platform.io</li>
                <li>Cursor</li>
              </ul>
            </li>
            <li>
              <h4 style="text-decoration: underline;">Database</h4>
              <ul>
                <li>MongoDB</li>
                <li>Mongoose</li>
              </ul>
            </li>
            <li>
              <h4 style="text-decoration: underline;">Frameworks</h4>
              <ul>
                <li>React Native</li>
                <li>NestJS</li>
              </ul>
            </li>
            <li>
              <h4 style="text-decoration: underline;">Security</h4>
              <ul>
                <li>OAuth</li>
              </ul>
            </li>
          </ul>
        </td>
      </tr>
    </table>
  </div>

  <h4 style="margin-top: 2rem; font-size: 1.5rem; font-weight: bold;">What inspired this project and how was it developed?</h4>
  <p style="max-width: 800px; margin: 0 auto; font-size: 1rem; color: #555; text-align: justify;">
    Being born on the Caribbean Island of Trinidad, I was used to Sunday markets, where farmers would gather to sell their natural, organic produce. During my time in the USA, I began developing allergic reactions to fruit I was accustomed to eating. The uncertainty surrounding the labeling of "organic" inspired this project. With my coding background, I embarked on a mission to create a self-sustainable farm that reduces the large-scale footprint of farming while ensuring transparency in the process.
  </p>

  <h4 style="margin-top: 2rem; font-size: 1.5rem; font-weight: bold;">How did the project look in the past?</h4>
  <div style="display: flex; flex-wrap: wrap; justify-content: center; gap: 15px; margin-top: 1rem;">
    <img src="https://github.com/IamDaleon/SolarHydroPonics/blob/master/img/schema.JPG" width="300" alt="Schematics" style="border: 1px solid #ddd; border-radius: 8px;">
    <img src="https://github.com/IamDaleon/SolarHydroPonics/blob/master/img/brains.jpg" width="300" alt="Brains" style="border: 1px solid #ddd; border-radius: 8px;">
    <img src="https://github.com/IamDaleon/SolarHydroPonics/blob/master/img/solarpanel.JPG" width="300" alt="Solar Panel" style="border: 1px solid #ddd; border-radius: 8px;">
    <img src="https://github.com/IamDaleon/SolarHydroPonics/blob/master/img/battery.JPG" width="300" alt="Battery Bank" style="border: 1px solid #ddd; border-radius: 8px;">
    <img src="https://github.com/IamDaleon/SolarHydroPonics/blob/master/img/first_connect.jpeg" width="300" alt="First Connection" style="border: 1px solid #ddd; border-radius: 8px;">
    <img src="https://github.com/IamDaleon/SolarHydroPonics/blob/master/img/connected.jpg" width="300" alt="First Initialization" style="border: 1px solid #ddd; border-radius: 8px;">
    <img src="https://github.com/IamDaleon/SolarHydroPonics/blob/master/img/display.jpg" width="300" alt="First Readout" style="border: 1px solid #ddd; border-radius: 8px;">
  </div>
</div>
