const path = require('path')

const rootDir = path.resolve(__dirname, "./");
const assetUrl = path.resolve(rootDir, "assets/icons");

export const WeatherIcon = props => {
    const iconId = props.icon || "na";
    const imageUrl = `${path.resolve(assetUrl, `${iconId}.png`)}`;
    return (
      <image
        style={props.style || ""}
        src={imageUrl}
        scaledContent={true}
      />
    );
};