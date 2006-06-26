package com.facebook.thrift.protocol;

import com.facebook.thrift.types.*;

/**
 * Helper class that encapsulates set metadata.
 *
 * @author Mark Slee <mcslee@facebook.com>
 */
public class TSet {
  public TSet() {}

  public TSet(TType t, int s) {
    this(t, new Int32(s));
  }

  public TSet(TType t, Int32 s) {
    elemType = t;
    size = s;
  }

  public TType  elemType = TType.STOP;
  public Int32 size = new Int32();
}
