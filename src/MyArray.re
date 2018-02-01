let head = (arr: array('a)) : option('a) =>
  if (Array.length(arr) > 0) {
    Some(arr[0]);
  } else {
    None;
  };
