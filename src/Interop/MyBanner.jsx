import React from 'react';

const MyBanner = (props) => {
    if (props.show) {
      return <div>{props.message}</div>
    } else {
      return null;
    }
};
// module.exports = MyBanner;

export default MyBanner;
