/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtCharts/QXYSeries>
#include <private/qxyseries_p.h>
#include <private/abstractdomain_p.h>
#include <QtCharts/QValueAxis>
#include <private/xychart_p.h>
#include <QtCharts/QXYLegendMarker>
#include <private/charthelpers_p.h>
#include <private/qchart_p.h>
#include <QtGui/QPainter>

QT_BEGIN_NAMESPACE

/*!
    \class QXYSeries
    \inmodule QtCharts
    \brief The QXYSeries class is a base class for line, spline, and scatter
    series.

    QXYSeries supports displaying best fit line on a chart. Best fit line is a line
    through a chart that expresses the relationship between points.
*/
/*!
    \qmltype XYSeries
    \instantiates QXYSeries
    \inqmlmodule QtCharts

    \inherits AbstractSeries

    \brief A base type for line, spline, and scatter series.

    XYSeries supports displaying best fit line on a chart. Best fit line is a line
    through a chart that expresses the relationship between points.
*/

/*!
    \qmlproperty AbstractAxis XYSeries::axisX
    The x-axis used for the series. If you leave both axisX and axisXTop
    undefined, a value axis is created for the series.
    \sa axisXTop, ValueAxis
*/

/*!
    \qmlproperty AbstractAxis XYSeries::axisY
    The y-axis used for the series. If you leave both axisY and axisYRight
    undefined, a value axis is created for the series.
    \sa axisYRight, ValueAxis
*/

/*!
    \qmlproperty AbstractAxis XYSeries::axisXTop
    The x-axis used for the series, drawn on top of the chart view.

    \note You can only provide either axisX or axisXTop, not both.
    \sa axisX
*/

/*!
    \qmlproperty AbstractAxis XYSeries::axisYRight
    The y-axis used for the series, drawn to the right on the chart view.

    \note You can only provide either axisY or axisYRight, not both.
    \sa axisY
*/

/*!
    \qmlproperty AbstractAxis XYSeries::axisAngular
    The angular axis used for the series, drawn around the polar chart view.
    \sa axisX
*/

/*!
    \qmlproperty AbstractAxis XYSeries::axisRadial
    The radial axis used for the series, drawn inside the polar chart view.
    \sa axisY
*/

/*!
    \property QXYSeries::pointsVisible
    \brief Whether the data points are visible and should be drawn.
*/
/*!
    \qmlproperty bool XYSeries::pointsVisible
    Whether the data points are visible and should be drawn.
*/

/*!
   \fn QPen QXYSeries::pen() const
   Returns the pen used to draw the outline of the data points for the series.
    \sa setPen()
*/

/*!
   \fn QBrush QXYSeries::brush() const
   Returns the brush used to fill the data points for the series.
    \sa setBrush()
*/

/*!
    \property QXYSeries::color
    \brief The color of the series.

    This is the line (pen) color in case of QLineSeries or QSplineSeries and the
    fill (brush) color in case of QScatterSeries or QAreaSeries.
    \sa pen(), brush()
*/
/*!
    \qmlproperty color XYSeries::color
    The color of the series. This is the line (pen) color in case of LineSeries
    or SplineSeries and the fill (brush) color in case of ScatterSeries or
    AreaSeries.
*/

/*!
    \property QXYSeries::pointLabelsFormat
    \brief The format used for showing labels with data points.

    QXYSeries supports the following format tags:
    \table
      \row
        \li @xPoint      \li The x-coordinate of the data point.
      \row
        \li @yPoint      \li The y-coordinate of the data point.
    \endtable

    For example, the following usage of the format tags would produce labels
    that display the data point shown inside brackets separated by a comma
    (x, y):

    \code
    series->setPointLabelsFormat("(@xPoint, @yPoint)");
    \endcode

    By default, the labels' format is set to \c {@xPoint, @yPoint}. The labels
    are shown on the plot area, and the labels on the edge of the plot area are
    cut. If the points are close to each other, the labels may overlap.

    \sa pointLabelsVisible, pointLabelsFont, pointLabelsColor
*/
/*!
    \qmlproperty string XYSeries::pointLabelsFormat
    The format used for showing labels with data points.

    \sa pointLabelsVisible, pointLabelsFont, pointLabelsColor
*/
/*!
    \fn void QXYSeries::pointLabelsFormatChanged(const QString &format)
    This signal is emitted when the format of data point labels changes to
    \a format.
*/

/*!
    \property QXYSeries::pointLabelsVisible
    \brief The visibility of data point labels.

    This property is \c false by default.

    \sa pointLabelsFormat, pointLabelsClipping
*/
/*!
    \qmlproperty bool XYSeries::pointLabelsVisible
    The visibility of data point labels. This property is \c false by default.

    \sa pointLabelsFormat, pointLabelsClipping
*/
/*!
    \fn void QXYSeries::pointLabelsVisibilityChanged(bool visible)
    This signal is emitted when the visibility of the data point labels
    changes to \a visible.
*/

/*!
    \property QXYSeries::pointLabelsFont
    \brief The font used for data point labels.

    \sa pointLabelsFormat
*/
/*!
    \qmlproperty font XYSeries::pointLabelsFont
    The font used for data point labels.

    \sa pointLabelsFormat
*/
/*!
    \fn void QXYSeries::pointLabelsFontChanged(const QFont &font);
    This signal is emitted when the font used for data point labels changes to
    \a font.
*/

/*!
    \property QXYSeries::pointLabelsColor
    \brief The color used for data point labels. By default, the color is the color of the brush
    defined in theme for labels.

    \sa pointLabelsFormat
*/
/*!
    \qmlproperty font XYSeries::pointLabelsColor
    The color used for data point labels. By default, the color is the color of the brush
    defined in theme for labels.

    \sa pointLabelsFormat
*/
/*!
    \fn void QXYSeries::pointLabelsColorChanged(const QColor &color);
    This signal is emitted when the color used for data point labels changes to
    \a color.
*/

/*!
    \property QXYSeries::pointLabelsClipping
    \brief The clipping for data point labels.

    This property is \c true by default. The labels on the edge of the plot area
    are cut when clipping is enabled.

    \sa pointLabelsVisible
*/
/*!
    \qmlproperty bool XYSeries::pointLabelsClipping
    The clipping for data point labels. This property is \c true by default. The
    labels on the edge of the plot area are cut when clipping is enabled.

    \sa pointLabelsVisible
*/
/*!
    \property QXYSeries::selectedColor
    \brief The color of the selected points.

    This is the fill (brush) color of points marked as selected. If not specified,
    value of QXYSeries::color is used as default.
    \sa color
    \since 6.2
*/
/*!
    \qmlproperty color XYSeries::selectedColor
    The color of the selected points. This is the fill (brush) color of points marked
    as selected.
    If not specified, value of QXYSeries::color is used as default.
    \sa color
*/
/*!
    \fn void QXYSeries::pointLabelsClippingChanged(bool clipping)
    This signal is emitted when the clipping of the data point labels changes to
    \a clipping.
*/
/*!
    \property QXYSeries::bestFitLineVisible
    \brief The visibility of the best fit line.

    This property is \c false by default.

    \sa bestFitLineEquation
    \since 6.2
*/
/*!
    \qmlproperty bool XYSeries::bestFitLineVisible
    The visibility of the best fit line.
    This property is \c false by default.
*/
/*!
    \fn void QXYSeries::bestFitLineVisibilityChanged(bool visible)
    This signal is emitted when the visibility of the best fit line changes to
    \a visible.
*/
/*!
    \property QXYSeries::bestFitLineColor
    \brief The color of best fit line.

    \sa bestFitLineEquation, bestFitLineVisible
    \since 6.2
*/
/*!
    \qmlproperty bool XYSeries::bestFitLineColor
    The color of best fit line.
    \sa bestFitLineVisible
*/
/*!
    \fn void QXYSeries::bestFitLineColorChanged(const QColor &color)
    This signal is emitted when the color used for the best fit line changes to
    \a color.
*/

/*!
    \fn void QXYSeries::clicked(const QPointF& point)
    This signal is emitted when the user triggers a mouse event by
    clicking the point \a point in the chart.

    \sa pressed(), released(), doubleClicked()
*/
/*!
    \qmlsignal XYSeries::clicked(point point)
    This signal is emitted when the user triggers a mouse event by clicking the
    point \a point in the chart. For example:
    \code
    LineSeries {
        XYPoint { x: 0; y: 0 }
        XYPoint { x: 1.1; y: 2.1 }
        onClicked: console.log("onClicked: " + point.x + ", " + point.y);
    }
    \endcode

    The corresponding signal handler is \c onClicked().

    \sa pressed(), released(), doubleClicked()
*/

/*!
    \fn void QXYSeries::hovered(const QPointF &point, bool state)
    This signal is emitted when a mouse is hovered over the point \a point in
    the chart. When the mouse moves over the point, \a state turns \c true,
    and when the mouse moves away again, it turns \c false.
*/
/*!
    \qmlsignal XYSeries::hovered(point point, bool state)
    This signal is emitted when a mouse is hovered over the point \a point in
    the chart. When the mouse moves over the point, \a state turns \c true,
    and when the mouse moves away again, it turns \c false.

    The corresponding signal handler is \c onHovered().
*/

/*!
    \fn void QXYSeries::pressed(const QPointF& point)
    This signal is emitted when the user presses the data point \a point in the
    chart and holds down the mouse button.

    \sa clicked(), released(), doubleClicked()
*/
/*!
    \qmlsignal XYSeries::pressed(point point)
    This signal is emitted when the user presses the data point \a point in the
    chart and holds down the mouse button. For example:
    \code
    LineSeries {
        XYPoint { x: 0; y: 0 }
        XYPoint { x: 1.1; y: 2.1 }
        onPressed: console.log("onPressed: " + point.x + ", " + point.y);
    }
    \endcode

    The corresponding signal handler is \c onPressed().

    \sa clicked(), released(), doubleClicked()
*/

/*!
    \fn void QXYSeries::released(const QPointF& point)
    This signal is emitted when the user releases the mouse press on the data
    point specified by \a point.
    \sa pressed(), clicked(), doubleClicked()
*/
/*!
    \qmlsignal XYSeries::released(point point)
    This signal is emitted when the user releases the mouse press on the data
    point specified by \a point.
    For example:
    \code
    LineSeries {
        XYPoint { x: 0; y: 0 }
        XYPoint { x: 1.1; y: 2.1 }
        onReleased: console.log("onReleased: " + point.x + ", " + point.y);
    }
    \endcode

    The corresponding signal handler is \c onReleased().

    \sa pressed(), clicked(), doubleClicked()
*/

/*!
    \fn void QXYSeries::doubleClicked(const QPointF& point)
    This signal is emitted when the user double-clicks the data point \a point
    in the chart. The \a point is the point where the first press was triggered.
    \sa pressed(), released(), clicked()
*/
/*!
    \qmlsignal XYSeries::doubleClicked(point point)
    This signal is emitted when the user double-clicks the data point \a point
    in the chart. The \a point is the point where the first press was triggered.
    For example:
    \code
    LineSeries {
        XYPoint { x: 0; y: 0 }
        XYPoint { x: 1.1; y: 2.1 }
        onDoubleClicked: console.log("onDoubleClicked: " + point.x + ", " + point.y);
    }
    \endcode

    The corresponding signal handler is \c onDoubleClicked().

    \sa pressed(), released(), clicked()
*/

/*!
    \fn void QXYSeries::pointReplaced(int index)
    This signal is emitted when a point is replaced at the position specified by
    \a index.
    \sa replace()
*/
/*!
    \qmlsignal XYSeries::pointReplaced(int index)
    This signal is emitted when a point is replaced at the position specified by
    \a index.

    The corresponding signal handler is \c onPointReplaced().
*/

/*!
    \fn void QXYSeries::pointsReplaced()
    This signal is emitted when all points are replaced with other points.
    \sa replace()
*/
/*!
    \qmlsignal XYSeries::pointsReplaced()
    This signal is emitted when all points are replaced with other points.

    The corresponding signal handler is \c onPointsReplaced().
*/

/*!
    \fn void QXYSeries::pointAdded(int index)
    This signal is emitted when a point is added at the position specified by
    \a index.
    \sa append(), insert()
*/
/*!
    \qmlsignal XYSeries::pointAdded(int index)
    This signal is emitted when a point is added at the position specified by
    \a index.

    The corresponding signal handler is \c onPointAdded().
*/

/*!
    \fn void QXYSeries::pointRemoved(int index)
    This signal is emitted when a point is removed from the position specified
    by \a index.
    \sa remove()
*/

/*!
    \qmlsignal XYSeries::pointRemoved(int index)
    This signal is emitted when a point is removed from the position specified
    by \a index.

    The corresponding signal handler is \c onPointRemoved().
*/

/*!
    \fn void QXYSeries::pointsRemoved(int index, int count)
    This signal is emitted when the number of points specified by \a count
    is removed starting at the position specified by \a index.
    \sa removePoints(), clear()
*/

/*!
    \qmlsignal XYSeries::pointsRemoved(int index, int count)
    This signal is emitted when the number of points specified by \a count
    is removed starting at the position specified by \a index.

    The corresponding signal handler is \c onPointRemoved().
*/

/*!
    \fn void QXYSeries::colorChanged(QColor color)
    This signal is emitted when the line (pen) color changes to \a color.
*/

/*!
    \fn void QXYSeries::penChanged(const QPen &pen)
    This signal is emitted when the pen changes to \a pen.
*/

/*!
    \fn void QXYSeries::lightMarkerChanged(const QImage &lightMarker)
    This signal is emitted when the light marker image changes to \a lightMarker.
    \sa QXYSeries::setLightMarker();
    \since 6.2
*/

/*!
    \fn void QXYSeriesPrivate::updated()
    \internal
*/

/*!
    \qmlmethod XYSeries::append(real x, real y)
    Appends a point with the coordinates \a x and \a y to the series.
*/

/*!
    \qmlmethod XYSeries::replace(real oldX, real oldY, real newX, real newY)
    Replaces the point with the coordinates \a oldX and \a oldY with the point
    with the coordinates \a newX and \a newY. Does nothing if the old point does
    not exist.
*/

/*!
    \qmlmethod XYSeries::remove(real x, real y)
    Removes the point with the coordinates \a x and \a y from the series. Does
    nothing if the point does not exist.
*/

/*!
    \qmlmethod XYSeries::remove(int index)
    Removes the point at the position specified by \a index from the series.
*/

/*!
    \qmlmethod XYSeries::removePoints(int index, int count)
    Removes the number of points specified by \a count from the series starting
    at the position specified by \a index.
*/

/*!
    \qmlmethod XYSeries::insert(int index, real x, real y)
    Inserts a point with the coordinates \a x and \a y to the position specified
    by \a index in the series. If the index is 0 or less than 0, the point is
    prepended to the list of points. If the index is equal to or greater than
    than the number of points in the series, the point is appended to the
    list of points.
*/

/*!
    \qmlmethod QPointF XYSeries::at(int index)
    Returns the point at the position specified by \a index. Returns (0, 0) if
    the index is not valid.
*/

/*!
    \internal

    Constructs an empty series object that is a child of \a parent.
    When the series object is added to QChart, instance ownerships is transferred.
*/
QXYSeries::QXYSeries(QXYSeriesPrivate &d, QObject *parent)
    : QAbstractSeries(d, parent)
{
}

/*!
    Deletes the series. Series added to QChart instances are owned by them,
    and are deleted when the QChart instances are deleted.
*/
QXYSeries::~QXYSeries()
{
}

/*!
    Adds the data point with the coordinates \a x and \a y to the series.
 */
void QXYSeries::append(qreal x, qreal y)
{
    append(QPointF(x, y));
}

/*!
   \overload
   Adds the data point \a point to the series.
 */
void QXYSeries::append(const QPointF &point)
{
    Q_D(QXYSeries);

    if (isValidValue(point)) {
        d->m_points << point;
        emit pointAdded(d->m_points.count() - 1);
    }
}

/*!
   \overload
   Adds the list of data points specified by \a points to the series.
 */
void QXYSeries::append(const QList<QPointF> &points)
{
    foreach (const QPointF &point , points)
        append(point);
}

/*!
    Replaces the point with the coordinates \a oldX and \a oldY with the point
    with the coordinates \a newX and \a newY. Does nothing if the old point does
    not exist.

    \sa pointReplaced()
*/
void QXYSeries::replace(qreal oldX, qreal oldY, qreal newX, qreal newY)
{
    replace(QPointF(oldX, oldY), QPointF(newX, newY));
}

/*!
  Replaces the point specified by \a oldPoint with the one specified by
  \a newPoint.
  \sa pointReplaced()
*/
void QXYSeries::replace(const QPointF &oldPoint, const QPointF &newPoint)
{
    Q_D(QXYSeries);
    int index = d->m_points.indexOf(oldPoint);
    if (index == -1)
        return;
    replace(index, newPoint);
}

/*!
  Replaces the point at the position specified by \a index with the point that
  has the coordinates \a newX and \a newY.
  \sa pointReplaced()
*/
void QXYSeries::replace(int index, qreal newX, qreal newY)
{
    replace(index, QPointF(newX, newY));
}

/*!
  Replaces the point at the position specified by \a index with the point
  specified by \a newPoint.
  \sa pointReplaced()
*/
void QXYSeries::replace(int index, const QPointF &newPoint)
{
    Q_D(QXYSeries);
    if (isValidValue(newPoint)) {
        d->m_points[index] = newPoint;
        emit pointReplaced(index);
    }
}

/*!
  Replaces the current points with the points specified by \a points.
  \note This is much faster than replacing data points one by one,
  or first clearing all data, and then appending the new data. Emits QXYSeries::pointsReplaced()
  when the points have been replaced.
  \sa pointsReplaced()
*/
void QXYSeries::replace(const QList<QPointF> &points)
{
    Q_D(QXYSeries);
    d->m_points = points;
    emit pointsReplaced();
}

/*!
   Returns true if point at given \a index is among selected points and false otherwise.
   \note Selected points are drawn using the selected color if it was specified.
   \sa selectedPoints(), setPointSelected(), setSelectedColor()
   \since 6.2
 */
bool QXYSeries::isPointSelected(int index)
{
    Q_D(QXYSeries);
    return d->isPointSelected(index);
}

/*!
  Marks point at \a index as selected.
  \note Emits QXYSeries::selectedPointsChanged
  \sa setPointSelected()
  \since 6.2
 */
void QXYSeries::selectPoint(int index)
{
    setPointSelected(index, true);
}

/*!
  Deselects point at given \a index.
  \note Emits QXYSeries::selectedPointsChanged
  \sa setPointSelected()
  \since 6.2
 */
void QXYSeries::deselectPoint(int index)
{
    setPointSelected(index, false);
}

/*!
  Marks point at given \a index as either selected or deselected.
  \note Selected points are drawn using the selected color if it was specified. Emits QXYSeries::selectedPointsChanged
  \sa setPointSelected(), setSelectedColor()
  \since 6.2
 */
void QXYSeries::setPointSelected(int index, bool selected)
{
    Q_D(QXYSeries);

    bool callSignal = false;
    d->setPointSelected(index, selected, callSignal);

    if (callSignal)
        emit selectedPointsChanged();
}

/*!
  Marks all points in the series as selected,
  \note Emits QXYSeries::selectedPointsChanged
  \sa setPointSelected()
  \since 6.2
 */
void QXYSeries::selectAllPoints()
{
    Q_D(QXYSeries);

    bool callSignal = false;
    for (int i = 0; i < d->m_points.count(); ++i)
        d->setPointSelected(i, true, callSignal);

    if (callSignal)
        emit selectedPointsChanged();
}

/*!
  Deselects all points in the series.
  \note Emits QXYSeries::selectedPointsChanged
  \sa setPointSelected()
  \since 6.2
 */
void QXYSeries::deselectAllPoints()
{
    Q_D(QXYSeries);

    bool callSignal = false;
    for (int i = 0; i < d->m_points.count(); ++i)
        d->setPointSelected(i, false, callSignal);

    if (callSignal)
        emit selectedPointsChanged();
}

/*!
  Marks multiple points passed in a \a indexes list as selected.
  \note Emits QXYSeries::selectedPointsChanged
  \sa setPointSelected()
  \since 6.2
 */
void QXYSeries::selectPoints(const QList<int> &indexes)
{
    Q_D(QXYSeries);

    bool callSignal = false;
    for (const int &index : indexes)
        d->setPointSelected(index, true, callSignal);

    if (callSignal)
        emit selectedPointsChanged();
}

/*!
  Marks multiple points passed in a \a indexes list as deselected.
  \note Emits QXYSeries::selectedPointsChanged
  \sa setPointSelected()
  \since 6.2
 */
void QXYSeries::deselectPoints(const QList<int> &indexes)
{
    Q_D(QXYSeries);

    bool callSignal = false;
    for (const int &index : indexes)
        d->setPointSelected(index, false, callSignal);

    if (callSignal)
        emit selectedPointsChanged();
}

/*!
  Changes selection state of points at given \a indexes to the opposite one. Makes
  \note Emits QXYSeries::selectedPointsChanged
  \sa setPointSelected()
  \since 6.2
 */
void QXYSeries::toggleSelection(const QList<int> &indexes)
{
    Q_D(QXYSeries);

    bool callSignal = false;
    for (const int &index : indexes)
        d->setPointSelected(index, !isPointSelected(index), callSignal);

    if (callSignal)
        emit selectedPointsChanged();
}

/*!
  Returns a list of points indexes marked as selected.
  Selected points are visible regardless of points visibility.
  \sa setPointSelected(), pointsVisible()
  \since 6.2
 */
QList<int> QXYSeries::selectedPoints() const
{
    Q_D(const QXYSeries);
    return QList<int>(d->m_selectedPoints.begin(), d->m_selectedPoints.end());
}

/*!
  Removes the point that has the coordinates \a x and \a y from the series.
  \sa pointRemoved()
*/
void QXYSeries::remove(qreal x, qreal y)
{
    remove(QPointF(x, y));
}

/*!
  Removes the data point \a point from the series.
  \sa pointRemoved()
*/
void QXYSeries::remove(const QPointF &point)
{
    Q_D(QXYSeries);
    int index = d->m_points.indexOf(point);
    if (index == -1)
        return;
    remove(index);
}

/*!
  Removes the point at the position specified by \a index from the series.
  \sa pointRemoved()
*/
void QXYSeries::remove(int index)
{
    Q_D(QXYSeries);
    deselectPoint(index);
    d->m_points.remove(index);
    emit pointRemoved(index);
}

/*!
  Removes the number of points specified by \a count from the series starting at
  the position specified by \a index.
  \sa pointsRemoved()
*/
void QXYSeries::removePoints(int index, int count)
{
    // This function doesn't overload remove as there is chance for it to get mixed up with
    // remove(qreal, qreal) overload in some implicit casting cases.
    Q_D(QXYSeries);
    if (count > 0) {
        if (!d->m_selectedPoints.empty()) {
            QList<int> indexes;
            for (int i = index; i < index + count; ++i)
                indexes << i;
            deselectPoints(indexes);
        }

        d->m_points.remove(index, count);
        emit pointsRemoved(index, count);
    }
}

/*!
  Inserts the data point \a point in the series at the position specified by
  \a index.
  \sa pointAdded()
*/
void QXYSeries::insert(int index, const QPointF &point)
{
    Q_D(QXYSeries);
    if (isValidValue(point)) {
        index = qMax(0, qMin(index, d->m_points.size()));

        if (!d->m_selectedPoints.isEmpty()) {
            // if point was inserted we need to move already selected points by 1
            QSet<int> selectedAfterInsert;
            bool callSignal = false;
            for (const auto &value : d->m_selectedPoints) {
                if (value >= index) {
                    selectedAfterInsert << value + 1;
                    callSignal = true;
                } else {
                    selectedAfterInsert << value;
                }
            }
            d->m_selectedPoints = selectedAfterInsert;
            if (callSignal)
                emit selectedPointsChanged();
        }

        d->m_points.insert(index, point);
        emit pointAdded(index);
    }
}

/*!
  Removes all points from the series.
  \sa pointsRemoved()
*/
void QXYSeries::clear()
{
    Q_D(QXYSeries);
    removePoints(0, d->m_points.size());
}

/*!
    Returns the points in the series.
*/
QList<QPointF> QXYSeries::points() const
{
    Q_D(const QXYSeries);
    return d->m_points;
}

#if QT_DEPRECATED_SINCE(6, 0)
/*!
    \obsolete

    Use points() instead.
    Returns the points in the series.

*/
QList<QPointF> QXYSeries::pointsVector() const
{
    Q_D(const QXYSeries);
    return d->m_points;
}
#endif

/*!
    Returns the data point at the position specified by \a index in the internal
    series of points.
*/
const QPointF &QXYSeries::at(int index) const
{
    Q_D(const QXYSeries);
    return d->m_points.at(index);
}

/*!
    Returns the number of data points in a series.
*/
int QXYSeries::count() const
{
    Q_D(const QXYSeries);
    return d->m_points.count();
}


/*!
    Sets the pen used for drawing points on the chart to \a pen. If the pen is
    not defined, the pen from the chart theme is used.
    \sa QChart::setTheme()
*/
void QXYSeries::setPen(const QPen &pen)
{
    Q_D(QXYSeries);
    if (d->m_pen != pen) {
        bool emitColorChanged = d->m_pen.color() != pen.color();
        d->m_pen = pen;
        emit d->updated();
        if (emitColorChanged)
            emit colorChanged(pen.color());
        emit penChanged(pen);
    }
}

QPen QXYSeries::pen() const
{
    Q_D(const QXYSeries);
    if (d->m_pen == QChartPrivate::defaultPen())
        return QPen();
    else
        return d->m_pen;
}

/*!
    Sets the brush used for drawing points on the chart to \a brush. If the
    brush is not defined, the brush from the chart theme setting is used.
    \sa QChart::setTheme()
*/
void QXYSeries::setBrush(const QBrush &brush)
{
    Q_D(QXYSeries);
    if (d->m_brush != brush) {
        d->m_brush = brush;
        emit d->updated();
    }
}

QBrush QXYSeries::brush() const
{
    Q_D(const QXYSeries);
    if (d->m_brush == QChartPrivate::defaultBrush())
        return QBrush();
    else
        return d->m_brush;
}

void QXYSeries::setColor(const QColor &color)
{
    QPen p = pen();
    if (p.color() != color) {
        p.setColor(color);
        setPen(p);
    }
}

QColor QXYSeries::color() const
{
    return pen().color();
}

void QXYSeries::setSelectedColor(const QColor &color)
{
    Q_D(QXYSeries);
    if (selectedColor() != color) {
        d->m_selectedColor = color;
        emit selectedColorChanged(color);
    }
}

QColor QXYSeries::selectedColor() const
{
    Q_D(const QXYSeries);
    return d->m_selectedColor;
}

void QXYSeries::setPointsVisible(bool visible)
{
    Q_D(QXYSeries);
    if (d->m_pointsVisible != visible) {
        d->m_pointsVisible = visible;
        emit d->updated();
    }
}

bool QXYSeries::pointsVisible() const
{
    Q_D(const QXYSeries);
    return d->m_pointsVisible;
}

void QXYSeries::setPointLabelsFormat(const QString &format)
{
    Q_D(QXYSeries);
    if (d->m_pointLabelsFormat != format) {
        d->m_pointLabelsFormat = format;
        emit pointLabelsFormatChanged(format);
    }
}

QString QXYSeries::pointLabelsFormat() const
{
    Q_D(const QXYSeries);
    return d->m_pointLabelsFormat;
}

void QXYSeries::setPointLabelsVisible(bool visible)
{
    Q_D(QXYSeries);
    if (d->m_pointLabelsVisible != visible) {
        d->m_pointLabelsVisible = visible;
        emit pointLabelsVisibilityChanged(visible);
    }
}

bool QXYSeries::pointLabelsVisible() const
{
    Q_D(const QXYSeries);
    return d->m_pointLabelsVisible;
}

void QXYSeries::setPointLabelsFont(const QFont &font)
{
    Q_D(QXYSeries);
    if (d->m_pointLabelsFont != font) {
        d->m_pointLabelsFont = font;
        emit pointLabelsFontChanged(font);
    }
}

QFont QXYSeries::pointLabelsFont() const
{
    Q_D(const QXYSeries);
    return d->m_pointLabelsFont;
}

void QXYSeries::setPointLabelsColor(const QColor &color)
{
    Q_D(QXYSeries);
    if (d->m_pointLabelsColor != color) {
        d->m_pointLabelsColor = color;
        emit pointLabelsColorChanged(color);
    }
}

QColor QXYSeries::pointLabelsColor() const
{
    Q_D(const QXYSeries);
    if (d->m_pointLabelsColor == QChartPrivate::defaultPen().color())
        return QPen().color();
    else
        return d->m_pointLabelsColor;
}

void QXYSeries::setPointLabelsClipping(bool enabled)
{
    Q_D(QXYSeries);
    if (d->m_pointLabelsClipping != enabled) {
        d->m_pointLabelsClipping = enabled;
        emit pointLabelsClippingChanged(enabled);
    }
}

bool QXYSeries::pointLabelsClipping() const
{
    Q_D(const QXYSeries);
    return d->m_pointLabelsClipping;
}

/*!
    Sets the image used for drawing markers on each point of the series.

    The default value is a default-QImage() (QImage::isNull() == true), meaning no light marker
    will be painted.
    You can reset back to default (disabled) by calling this function with a null QImage (QImage()).

    The light markers visualize the data points of this series and as such are an alternative
    to setPointsVisible(true).
    Both features can be enabled independently from each other.

    Unlike the elements of \l {QScatterSeries}{QScatterSeries} the light markers
    are not represented by QGraphicsItem, but are just painted (no objects created).
    However, the mouse-event-signals of QXYSeries behave the same way,
    meaning that you'll get the exact domain value of the point if you click/press/hover
    the light marker. You'll still get the in between domain value if you click on the line.
    The light markers are above the line in terms of painting as well as events.

    \sa QXYSeries::lightMarker()
    \since 6.2
*/
void QXYSeries::setLightMarker(const QImage &lightMarker)
{
    Q_D(QXYSeries);
    if (d->m_lightMarker == lightMarker)
        return;

    d->m_lightMarker = lightMarker;
    emit lightMarkerChanged(d->m_lightMarker);
}

/*!
    Gets the image used for drawing markers on each point of the series.

    The default value is QImage(), meaning no light marker will be painted.

    The light markers visualize the data points of this series and as such are an alternative
    to setPointsVisible(true).
    Both features can be enabled independently from each other.

    Unlike the elements of \l {QScatterSeries}{QScatterSeries} the light markers
    are not represented by QGraphicsItem, but are just painted (no objects created).
    However, the mouse-event-signals of QXYSeries behave the same way,
    meaning that you'll get the exact domain value of the point if you click/press/hover
    the light marker. You'll still get the in between domain value if you click on the line.
    The light markers are above the line in terms of painting as well as events.
    \sa QXYSeries::setLightMarker()
    \since 6.2
*/
const QImage &QXYSeries::lightMarker() const
{
    Q_D(const QXYSeries);
    return d->m_lightMarker;
}

void QXYSeries::setBestFitLineVisible(bool visible)
{
    Q_D(QXYSeries);
    if (d->m_bestFitLineVisible != visible) {
        d->m_bestFitLineVisible = visible;
        emit bestFitLineVisibilityChanged(visible);
        emit d->updated();
    }
}

bool QXYSeries::bestFitLineVisible() const
{
    Q_D(const QXYSeries);
    return d->m_bestFitLineVisible;
}

/*!
    Returns a pair of numbers where the first number is a slope factor
    and the second number is intercept of a linear function for a best fit line.

    Those factors are calculated using Least Squares Method based
    on points passed to the series.

    Parameter \a ok is used to report a failure by setting its value to \c false
    and to report a success by setting its value to \c true.

    \sa QXYSeries::bestFitLineVisible()
    \since 6.2
*/
QPair<qreal, qreal> QXYSeries::bestFitLineEquation(bool &ok) const
{
    Q_D(const QXYSeries);
    return d->bestFitLineEquation(ok);
}

void QXYSeries::setBestFitLinePen(const QPen &pen)
{
    Q_D(QXYSeries);
    if (d->m_bestFitLinePen != pen) {
        bool emitColorChanged = d->m_bestFitLinePen.color() != pen.color();
        d->m_bestFitLinePen = pen;
        emit d->updated();
        if (emitColorChanged)
            bestFitLineColorChanged(pen.color());
        emit bestFitLinePenChanged(pen);
    }
}

QPen QXYSeries::bestFitLinePen() const
{
    Q_D(const QXYSeries);
    if (d->m_bestFitLinePen == QChartPrivate::defaultPen())
        return QPen();
    else
        return d->m_bestFitLinePen;
}

/*!
    Stream operator for adding the data point \a point to the series.
    \sa append()
*/
QXYSeries &QXYSeries::operator<< (const QPointF &point)
{
    append(point);
    return *this;
}


/*!
    Stream operator for adding the list of data points specified by \a points
    to the series.
    \sa append()
*/

QXYSeries &QXYSeries::operator<< (const QList<QPointF>& points)
{
    append(points);
    return *this;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QXYSeriesPrivate::QXYSeriesPrivate(QXYSeries *q)
    : QAbstractSeriesPrivate(q),
      m_pen(QChartPrivate::defaultPen()),
      m_brush(QChartPrivate::defaultBrush()),
      m_pointsVisible(false),
      m_pointLabelsFormat(QLatin1String("@xPoint, @yPoint")),
      m_pointLabelsVisible(false),
      m_pointLabelsFont(QChartPrivate::defaultFont()),
      m_pointLabelsColor(QChartPrivate::defaultPen().color()),
      m_pointLabelsClipping(true),
      m_bestFitLinePen(QChartPrivate::defaultPen()),
      m_bestFitLineVisible(false)
{
}

void QXYSeriesPrivate::initializeDomain()
{
    qreal minX(0);
    qreal minY(0);
    qreal maxX(1);
    qreal maxY(1);

    Q_Q(QXYSeries);

    const QList<QPointF> &points = q->points();

    if (!points.isEmpty()) {
        minX = points[0].x();
        minY = points[0].y();
        maxX = minX;
        maxY = minY;

        for (int i = 0; i < points.count(); i++) {
            qreal x = points[i].x();
            qreal y = points[i].y();
            minX = qMin(minX, x);
            minY = qMin(minY, y);
            maxX = qMax(maxX, x);
            maxY = qMax(maxY, y);
        }
    }

    domain()->setRange(minX, maxX, minY, maxY);
}

QList<QLegendMarker*> QXYSeriesPrivate::createLegendMarkers(QLegend* legend)
{
    Q_Q(QXYSeries);
    QList<QLegendMarker*> list;
    return list << new QXYLegendMarker(q,legend);
}

void QXYSeriesPrivate::initializeAxes()
{

}

QAbstractAxis::AxisType QXYSeriesPrivate::defaultAxisType(Qt::Orientation orientation) const
{
    Q_UNUSED(orientation);
    return QAbstractAxis::AxisTypeValue;
}

QAbstractAxis* QXYSeriesPrivate::createDefaultAxis(Qt::Orientation orientation) const
{
    Q_UNUSED(orientation);
    return new QValueAxis;
}

void QXYSeriesPrivate::initializeAnimations(QChart::AnimationOptions options,
                                            int duration, QEasingCurve &curve)
{
    XYChart *item = static_cast<XYChart *>(m_item.data());
    Q_ASSERT(item);
    if (item->animation())
        item->animation()->stopAndDestroyLater();

    if (options.testFlag(QChart::SeriesAnimations))
        item->setAnimation(new XYAnimation(item, duration, curve));
    else
        item->setAnimation(0);
    QAbstractSeriesPrivate::initializeAnimations(options, duration, curve);
}

void QXYSeriesPrivate::drawSeriesPointLabels(QPainter *painter, const QList<QPointF> &points,
                                             const int offset)
{
    if (points.size() == 0)
        return;

    static const QString xPointTag(QLatin1String("@xPoint"));
    static const QString yPointTag(QLatin1String("@yPoint"));
    const int labelOffset = offset + 2;

    QFont f(m_pointLabelsFont);
    f.setPixelSize(QFontInfo(m_pointLabelsFont).pixelSize());
    painter->setFont(f);
    painter->setPen(QPen(m_pointLabelsColor));
    QFontMetrics fm(painter->font());
    // m_points is used for the label here as it has the series point information
    // points variable passed is used for positioning because it has the coordinates
    const int pointCount = qMin(points.size(), m_points.size());
    for (int i(0); i < pointCount; i++) {
        QString pointLabel = m_pointLabelsFormat;
        pointLabel.replace(xPointTag, presenter()->numberToString(m_points.at(i).x()));
        pointLabel.replace(yPointTag, presenter()->numberToString(m_points.at(i).y()));

        // Position text in relation to the point
        int pointLabelWidth = fm.horizontalAdvance(pointLabel);
        QPointF position(points.at(i));
        position.setX(position.x() - pointLabelWidth / 2);
        position.setY(position.y() - labelOffset);

        painter->drawText(position, pointLabel);
    }
}

void QXYSeriesPrivate::drawBestFitLine(QPainter *painter, const QRectF &clipRect)
{
    bool ok = false;
    const auto &bestFitLineParams = bestFitLineEquation(ok);

    if (!ok)
        return;

    const qreal x1 = clipRect.x();
    const qreal y1 = bestFitLineParams.first * x1 + bestFitLineParams.second;
    QPointF p1 = domain()->calculateGeometryPoint(QPointF(x1, y1), ok);

    const qreal x2 = clipRect.x() + 1;
    const qreal y2 = bestFitLineParams.first * x2 + bestFitLineParams.second;
    QPointF p2 = domain()->calculateGeometryPoint(QPointF(x2, y2), ok);

    if (ok) {
        QLineF bestFitLine { p1, p2 };
        // maxLength is length of the diagonal, no line can be longer
        const qreal maxLength = qSqrt(qPow(clipRect.width(), 2) * qPow(clipRect.height(), 2));
        bestFitLine.setLength(maxLength);

        painter->save();
        painter->setPen(m_bestFitLinePen);
        painter->drawLine(bestFitLine);
        painter->restore();
    }
}

void QXYSeries::setBestFitLineColor(const QColor &color)
{
    QPen p = bestFitLinePen();
    if (p.color() != color) {
        p.setColor(color);
        setBestFitLinePen(p);
    }
}

QColor QXYSeries::bestFitLineColor() const
{
    return bestFitLinePen().color();
}

QPair<qreal, qreal> QXYSeriesPrivate::bestFitLineEquation(bool &ok) const
{
    if (m_points.count() <= 1) {
        ok = false;
        return { 0, 0 };
    }

    ok = true;
    qreal xSum = 0.0, x2Sum = 0.0, ySum = 0.0, xySum = 0.0;
    for (const auto &point : m_points) {
        xSum += point.x();
        ySum += point.y();
        x2Sum += qPow(point.x(), 2);
        xySum += point.x() * point.y();
    }

    const qreal divisor = m_points.count() * x2Sum - xSum * xSum;
    // To prevent crashes in unusual cases
    if (divisor == 0.0) {
        ok = false;
        return { 0, 0 };
    }

    qreal a = (m_points.count() * xySum - xSum * ySum) / divisor;
    qreal b = (x2Sum * ySum - xSum * xySum) / divisor;

    return { a, b };
}

void QXYSeriesPrivate::setPointSelected(int index, bool selected, bool &callSignal)
{
    if (index < 0 || index > m_points.count() - 1)
        return;

    if (selected) {
        if (!isPointSelected(index)) {
            m_selectedPoints << index;
            callSignal = true;
        }
    } else {
        if (isPointSelected(index)) {
            m_selectedPoints.remove(index);
            callSignal = true;
        }
    }
}

bool QXYSeriesPrivate::isPointSelected(int index)
{
    return m_selectedPoints.contains(index);
}

QT_END_NAMESPACE

#include "moc_qxyseries.cpp"
#include "moc_qxyseries_p.cpp"
